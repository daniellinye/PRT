using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Threading.Tasks;
using System.Data.SqlClient;
using System.Data.SqlTypes;
using System.Data.Sql;
using System.IO;
using Mono.Data.Sqlite;

namespace ChatServer
{
    class Database
    {

    }

    class Message
    {
        public string description;
        public DateTime datetime;
        public int senderId;
        public Message(string desc, DateTime date, int id)
        {
            description = desc;
            datetime = date;
            senderId = id;
        }
    }

    class DatabaseFunctions
    {
        public DatabaseFunctions()
        {
            connection = null;
            try
            {
                string localpath = @"users.mdf";
                connection = new SqlConnection("Data Source=(LocalDB)\\MSSQLLocalDB;AttachDbFilename=" + (Path.GetFullPath(localpath) + ";Integrated Security=True"));
                Console.WriteLine(DateTime.Now.ToString("[hh:mm:ss] ") + "Opening connection");
                connection.Open();

                Executecommand("INSERT INTO users(Id,username,password) VALUES(0,'Robert','wachtwoord')");
                Executecommand("INSERT INTO users(Id,username,password) VALUES(1,'Piet','wachtwoord')");
                Executecommand("INSERT INTO users(Id,username,password) VALUES(2,'Hein','wachtwoord')");

                Console.WriteLine(DateTime.Now.ToString("[hh:mm:ss] ") + "Connection Successful");
            }
            catch
            {
                try
                {
                    SqliteConnection.CreateFile("users.sqlite");
                    SqliteConnection scon = new SqliteConnection("Data Source=users.sqlite;Version=3;");
                    scon.Open();

                    StringBuilder sb = new StringBuilder();
                    sb.Append("CREATE TABLE users (");
                    sb.Append("Id       INT NOT NULL,");
                    sb.Append("username VARCHAR(10) NOT NULL,");
                    sb.Append("password VARCHAR(10) NOT NULL,");
                    sb.Append("online   BIT NULL,");
                    sb.Append("PRIMARY KEY (Id, username)");
                    sb.Append(");");
                    SqliteCommand command = new SqliteCommand(sb.ToString(), scon);
                    command.ExecuteNonQuery();

                    StringBuilder ub = new StringBuilder();
                    sb.Append("CREATE TABLE Messages (");
                    sb.Append("Mid       INT NOT NULL,");
                    sb.Append("description VARCHAR(255) NOT NULL,");
                    sb.Append("idfrom    INT NOT NULL,");
                    sb.Append("idto      INT NOT NULL,");
                    sb.Append("date      DATETIME");
                    sb.Append("PRIMARY KEY CLUSTERED(Mid ASC),");
                    sb.Append("FOREIGN KEY (idfrom) REFERENCES users(Id),");
                    sb.Append("FOREIGN KEY (idto) REFERENCES users(Id)");
                    sb.Append(");");
                    SqliteCommand command2 = new SqliteCommand(ub.ToString(), scon);
                    command2.ExecuteNonQuery();

                }
                catch (Exception e)
                {
                    Console.WriteLine(e);
                }

                Console.WriteLine(DateTime.Now.ToString("[hh:mm:ss] ") + "Connection Unsuccesfull");
            }
        }

        //executes a function on the database and returns values
        public bool ExecuteFunction(string function, string args)
        {
            //TODO:
            //add basic functionalities to login, getmessages
            //sendmessages, getuser, sendmessages and login
            string[] parser;
            List<Message> messages;
            switch (function)
            {
                case "Login":
                    parser = args.Split('.');
                    return LogIn(parser[0], parser[1]);
                case "Getmessages":
                    parser = args.Split('.');
                    messages = GetMessages(Convert.ToInt32(parser[0]));
                    return true;
                case "Message":
                    parser = args.Split(',');
                    return SendMessage(Convert.ToInt32(parser[0]),parser[1]);
                default:
                    Console.WriteLine(DateTime.Now.ToString("[hh:mm:ss] ") + "DatabaseFunction: " + function + " not recognized or implemented.");
                    break;
            }

            return false;
        }

        //logs user in if username and password match
        public bool LogIn(string username, string password)
        {
            try
            {
                bool exists = false;
                SqlDataReader reader = FetchData("SELECT * FROM users WHERE username='" + username + "'");
                while (reader != null && reader.Read())
                {
                    exists = true;
                    if ((string)reader["password"] == password)
                    {
                        userId = (int)reader["id"];
                        ingelogd = true;
                        Console.WriteLine(DateTime.Now.ToString("[hh:mm:ss] ") + "User: " + username + ", is logged in.");
                        reader.Close();
                        return true;
                    }
                    else
                    {
                        Console.WriteLine(DateTime.Now.ToString("[hh: mm:ss] ") + "Password incorrect.");
                    }
                }
                if (!exists)
                {
                    Console.WriteLine(DateTime.Now.ToString("[hh:mm:ss] ") + "Username does not exist.");
                }
                reader.Close();
                return false;
            }
            catch
            {
                Console.WriteLine("Log in attempt failed.");
                return false;
            }

        }

        public bool SendMessage(int toId, string description)
        {
            string format = "yyyy-MM-dd HH:mm:ss";
            return Executecommand("INSERT INTO Messages(Mid,description,idfrom,idto,datetime) VALUES(2,'" + description + "'," + userId + "," + toId + ",'" + DateTime.Now.ToString(format) + "')");
        }

        public List<Message> GetMessages(int buddyId)
        {
            if (ingelogd)
            {
                string description;
                int id;
                DateTime datetime;
                List<Message> messages = new List<Message>();

                SqlDataReader reader = FetchData("SELECT * FROM Messages WHERE (idfrom=" + userId +
                    " AND idto=" + buddyId + ")" + "OR idto=" + userId + " AND idfrom=" + buddyId + " ORDER BY datetime");

                while (reader.Read())
                {
                    description = (string)reader["description"];
                    datetime = (DateTime)reader["datetime"];
                    id = (int)reader["idfrom"];
                    messages.Add(new Message(description, datetime, id));
                }

                foreach (Message message in messages)
                {
                    Console.WriteLine("[" + message.datetime + "]" + message.description);
                }

                return messages;
            }
            return null;
        }

        public bool Executecommand(string query)
        {
            try
            {
                SqlCommand sqlcommand = new SqlCommand(query, connection);
                sqlcommand.ExecuteNonQuery();
                return true;
            }
            catch
            {
                Console.WriteLine(DateTime.Now.ToString("[hh:mm:ss] ") + "The query: \"" + query + "\" failed to be executed.");
                return false;
            }
        }


        public SqlDataReader FetchData(string query)
        {
            try
            {
                SqlCommand sqlcommand = new SqlCommand(query, connection);
                SqlDataReader reader = sqlcommand.ExecuteReader();
                return reader;

            }
            catch
            {
                Console.WriteLine(DateTime.Now.ToString("[hh:mm:ss] ") + "The query: \"" + query + "\" failed to be executed.");
                return null;
            }
        }

        private SqlConnection connection;
        private int userId;
        private bool ingelogd;
    }

}