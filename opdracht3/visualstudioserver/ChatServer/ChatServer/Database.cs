using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SqlClient;
using System.Data.SqlTypes;
using System.IO;


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
                
                Console.WriteLine(DateTime.Now.ToString("[hh:mm:ss] ") + "Connection Successful");

                ExecuteFunction("Login", "Robert.wachtwoord");
                ExecuteFunction("Login", "Daniel.wachtwoord");
                ExecuteFunction("Login", "Jelle.wachtwoord");
                ExecuteFunction("Login", "Yaboii.wachtwoord");
                ExecuteFunction("Login", "Piet.wachtwoord");
                GetUsers();
            }
            catch
            {
                try
                {
                    string connstring = "Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=ccwebgrity;Data Source=SURAJIT\\SQLEXPRESS";

                    string users = @"users.sql";
                    string path = File.ReadAllText(Path.GetFullPath(users));

                    connection = new SqlConnection(connstring);
                    SqlCommand command = new SqlCommand(path);
                    command.ExecuteNonQuery();
                }
                catch
                {
                    Console.WriteLine(DateTime.Now.ToString("[hh:mm:ss] ") + "Connection Unsuccesfull");
                }
                finally
                {
                    Console.WriteLine("First server not online, concluded we're running on Linux");
                }

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
                SqlDataReader reader = FetchData("SELECT * FROM users WHERE username='" + username + "'");
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
                reader.Close();
                if (!exists)
                {
                    CreateNewUser(username, password);
                }
                return false;
            }
            catch
            {
                Console.WriteLine("Log in attempt failed.");
                return false;
            }
        }

        //creates new user
        private bool CreateNewUser(string username, string password)
        {
            try
            {
                Executecommand("INSERT INTO users(Id,username,password,online) VALUES(" + NewUserId() + ",'" + username + "','" + password + "',1)");
                return true;
            }
            catch
            {
                Console.WriteLine("Failed to create new user");
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

                SqlDataReader reader = FetchData("SELECT * FROM Messages WHERE (idfrom=" + GetId(username) +
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

                return returnmessages;
            }
            return null;
        }

        //fetches all online users and returns list
        public List<string> GetUsers()
        {
            List<string> users = new List<string>();

            SqlDataReader reader = FetchData("SELECT username FROM users WHERE online=1");

            while (reader.Read())
            {
                users.Add((string)reader["username"]);
                Console.WriteLine(reader["username"]);
            }

            reader.Close();
            return users;
        }

        //returns id from username
        private int GetId(string username)
        {
            try
            {
                int id;

                SqlDataReader reader = FetchData("SELECT id FROM users WHERE username='" + username + "'");
                reader.Read();
                id = (int)reader["id"];
                reader.Close();

                return id;
            }
            catch
            {
                Console.WriteLine("Could not find id from user: " + username);
                return -1;
            }
        }

        //returns username from id
        private string GetUserName(int id)
        {
            string username;

            SqlDataReader reader = FetchData("SELECT username FROM users WHERE id='" + id + "'");
            reader.Read();
            username = (string)reader["username"];
            reader.Close();

            return username;
        }

        //returns whether user is logged in
        private bool Ingelogd(string username)
        {
            bool ingelogd = false;

            SqlDataReader reader = FetchData("SELECT online FROM users WHERE username='" + username + "'");
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
            SqlDataReader reader = FetchData("SELECT * FROM Messages");

            while (reader.Read())
            {
                messages.Add("");
            }
            reader.Close();

            return messages.Count;
        }

        //returns id for a new message
        private int NewUserId()
        {
            List<string> users = new List<string>();
            SqlDataReader reader = FetchData("SELECT * FROM users");

            while (reader.Read())
            {
                users.Add("");
            }
            reader.Close();

            return users.Count;
        }
        
        //executes sql query without return
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

        //executes sql query and returns the data as an SqlDataReader
        //after using this function and getting the data from the reader, the reader needs to be closed
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

        readonly private SqlConnection connection;
    }

}