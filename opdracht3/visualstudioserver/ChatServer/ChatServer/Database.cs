using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SqlClient;
using System.Data.SqlTypes;
using System.IO;
using System.Data.SQLite;


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

                SQLiteConnection.CreateFile("users.sqlite");
                connection = new SQLiteConnection("Data Source=users.sqlite;Version=3;");
                connection.Open();

                StringBuilder sb = new StringBuilder();
                sb.Append("CREATE TABLE users (");
                sb.Append("Id       INT NOT NULL,");
                sb.Append("username VARCHAR(10) NOT NULL,");
                sb.Append("password VARCHAR(10) NOT NULL,");
                sb.Append("online   BIT NULL,");
                sb.Append("PRIMARY KEY (Id, username)");
                sb.Append(");");
                SQLiteCommand command = new SQLiteCommand(sb.ToString(), connection);
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
                SQLiteCommand command2 = new SQLiteCommand(ub.ToString(), connection);
                command2.ExecuteNonQuery();


                Executecommand("INSERT INTO users(Id,username,password,online) VALUES(0,'Robert','wachtwoord',0)");
                Executecommand("INSERT INTO users(Id,username,password,online) VALUES(1,'Piet','wachtwoord',1)");
                Executecommand("INSERT INTO users(Id,username,password,online) VALUES(2,'Hein','wachtwoord',1)");

                Console.WriteLine(DateTime.Now.ToString("[hh:mm:ss] ") + "Connection Successful");
            }
            catch(Exception e)
            {
                Console.WriteLine(e);
                Console.ReadLine();
            }
            finally
            {
                Console.ReadLine();
            }
        }

        //executes a function on the database and returns values
        public bool ExecuteFunction(string function, string args)
        {
            //TODO:
            //add basic functionalities to login, getmessages
            //sendmessages, getuser, sendmessages and login
            string[] parser;
            switch (function)
            {
                case "Login":
                    parser = args.Split('.');
                    return LogIn(parser[0], parser[1]);
                case "Sendmessage":
                    parser = args.Split('.');
                    return SendMessage(parser[0], parser[1], parser[2]);
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
                SQLiteDataReader reader = FetchData("SELECT * FROM users WHERE username='" + username + "'");
                while (reader != null && reader.Read())
                {
                    exists = true;
                    if ((string)reader["password"] == password)
                    {                        
                        Console.WriteLine(DateTime.Now.ToString("[hh:mm:ss] ") + "User: " + username + ", is logged in.");
                        reader.Close();
                        Executecommand("UPDATE users SET online=1 WHERE username='" + username + "'");
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

        //sends message to database
        public bool SendMessage(string username, string description, string to)
        {
            string format = "yyyy-MM-dd HH:mm:ss";
            return Executecommand("INSERT INTO Messages(Mid,description,idfrom,idto,datetime) VALUES(" + NewMessageId() + ",'" + description + "'," + GetId(username) + "," + GetId(to) + ",'" + DateTime.Now.ToString(format) + "')");
        }

        //fetches all messages between user and contact
        public List<string> GetMessages(string username, string recieving)
        {
            if (Ingelogd(username))
            {
                string description;
                int id;
                DateTime datetime;
                List<Message> messages = new List<Message>();
                List<string> returnmessages = new List<string>();

                SQLiteDataReader reader = FetchData("SELECT * FROM Messages WHERE (idfrom=" + GetId(username) +
                    " AND idto=" + GetId(recieving) + ")" + "OR idto=" + GetId(username) + " AND idfrom=" + GetId(recieving) + " ORDER BY datetime");

                while (reader.Read())
                {
                    description = (string)reader["description"];
                    datetime = (DateTime)reader["datetime"];
                    id = (int)reader["idfrom"];
                    messages.Add(new Message(description,datetime,id));
                }

                reader.Close();

                foreach (Message message in messages)
                {
                    returnmessages.Add(GetUserName(message.senderId) + "`" + message.description + "`" + message.datetime);
                }

                foreach (string message in returnmessages)
                {
                    Console.WriteLine(message);
                }

                return returnmessages;
            }
            return null;
        }

        //fetches all online users and returns list
        public List<string> GetUsers()
        {
            List<string> users = new List<string>();

            SQLiteDataReader reader = FetchData("SELECT username FROM users WHERE online=1");

            while (reader.Read())
            {
                users.Add((string)reader["username"]);
            }

            reader.Close();
            return users;
        }

        //returns Id from username
        private int GetId(string username)
        {
            int id;

            SQLiteDataReader reader = FetchData("SELECT id FROM users WHERE username='" + username + "'");
            reader.Read();
            id = (int)reader["id"];
            reader.Close();

            return id;
        }

        private string GetUserName(int id)
        {
            string username;

            SqlDataReader reader = FetchData("SELECT username FROM users WHERE id='" + id + "'");
            reader.Read();
            username = (string)reader["username"];
            reader.Close();

            return username;
        }

        private bool Ingelogd(string username)
        {
            bool ingelogd = false;

            SQLiteDataReader reader = FetchData("SELECT online FROM users WHERE username='" + username + "'");
            while(reader.Read())
            {
                ingelogd = (bool)reader["online"];
            }
            reader.Close();

            return ingelogd;
        }

        //returns id for a new message
        private int NewMessageId ()
        {
            List<string> messages = new List<string>();
            SQLiteDataReader reader = FetchData("SELECT * FROM Messages");

            while (reader.Read())
            {
                messages.Add("");
            }
            reader.Close();

            return messages.Count;
        }

        //executes sql query without return
        public bool Executecommand(string query)
        {
            try
            {
                SQLiteCommand sqlcommand = new SQLiteCommand(query, connection);
                sqlcommand.ExecuteNonQuery();
                return true;
            }
            catch
            {
                Console.WriteLine(DateTime.Now.ToString("[hh:mm:ss] ") + "The query: \"" + query + "\" failed to be executed.");
                return false;
            }
        }

        //executes sql query and returns the data as an SqlDataReader
        //after using this function and getting the data from the reader, the reader needs to be closed
        public SQLiteDataReader FetchData(string query)
        {
            try
            {
                SQLiteCommand sqlcommand = new SQLiteCommand(query, connection);
                SQLiteDataReader reader = sqlcommand.ExecuteReader();
                return reader;

            }
            catch
            {
                Console.WriteLine(DateTime.Now.ToString("[hh:mm:ss] ") + "The query: \"" + query + "\" failed to be executed.");
                return null;
            }
        }

        readonly private SQLiteConnection connection;
    }

}