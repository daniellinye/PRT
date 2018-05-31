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
                connection = new SQLiteConnection("Data Source=users.sqlite;Version=3;");
                connection.Open();

                try
                {
                    StringBuilder sb = new StringBuilder();         //creates table users, if it does not exist already
                    sb.Append("CREATE TABLE users (");
                    sb.Append("Id       INT NOT NULL,");
                    sb.Append("username VARCHAR(10) NOT NULL,");
                    sb.Append("password VARCHAR(10) NOT NULL,");
                    sb.Append("online   BIT NULL,");
                    sb.Append("PRIMARY KEY (Id, username)");
                    sb.Append(");");
                    SQLiteCommand command = new SQLiteCommand(sb.ToString(), connection);
                    command.ExecuteNonQuery();
                }
                catch
                {

                }
                try
                {
                    StringBuilder ub = new StringBuilder();         //creates table Messages, if it does not exist already
                    ub.Append("CREATE TABLE Messages (");
                    ub.Append("Mid       INT PRIMARY KEY NOT NULL,");
                    ub.Append("description VARCHAR(255) NOT NULL,");
                    ub.Append("idfrom    INT NOT NULL,");
                    ub.Append("idto      INT NOT NULL,");
                    ub.Append("datetime      DATETIME,");
                    ub.Append("FOREIGN KEY (idfrom) REFERENCES users(Id),");
                    ub.Append("FOREIGN KEY (idto) REFERENCES users(Id)");
                    ub.Append(");");
                    SQLiteCommand command2 = new SQLiteCommand(ub.ToString(), connection);
                    command2.ExecuteNonQuery();
                }
                catch
                {

                }

                Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "Connection Successful.");

            }
            catch(Exception e)
            {
                Console.WriteLine("\n" + e + "\n");
                Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "Connection Unsuccesfull.");

            }
        }

        //executes a function on the database and returns values
        public bool ExecuteFunction(string function, string args)
        {
            string[] parser;        //This function is used for no-return functions, the arguments are split by dots.
            switch (function)       //This makes the amount of arguments is modular, the return is whether the function 
            {                       //was executed properly
                case "Login":
                    parser = args.Split('.');
                    return LogIn(parser[0], parser[1]);
                case "Sendmessage":
                    parser = args.Split('.');
                    return SendMessage(parser[0], parser[1], parser[2]);
                case "Register":
                    parser = args.Split('.');
                    return CreateNewUser(parser[0],parser[1]);
                default:
                    Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "DatabaseFunction: " + function + " not recognized or implemented.");
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
                        reader.Close();
                        Executecommand("UPDATE users SET online=1 WHERE username='" + username + "'");
                        Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "User: " + username + ", is logged in.");
                        return true;
                    }
                    else
                    {
                        Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "Password incorrect.");
                    }
                }
                reader.Close();
                if (!exists)
                {
                    Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "Username: " + username + " does not exist.");
                }
                return false;
            }
            catch
            {
                Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "Log in attempt failed.");
                return false;
            }
        }

        //logs user out
        private bool LogOut(string username)
        {
            try
            {
                Executecommand("UPDATE users SET online=0 WHERE username='" + username + "'");
                Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "User: " + username + ", is logged out.");
                return true;
            }
            catch
            {
                Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "User: " + username + ", could not be logged out.");
                return false;
            }
        }

        //creates new user
        private bool CreateNewUser(string username, string password)
        {
            const int minlength = 8;
            Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "Creating new user");
            try
            {
                if (password.Length >= minlength)
                {
                    Executecommand("INSERT INTO users(Id,username,password,online) VALUES(" + NewUserId() + ",'" + username + "','" + password + "',1)");
                    Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "User: " + username + " created.");
                    return true;
                }
                else
                {
                    Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "User was not created since the password was not long enough.");
                    return false;
                }
            }
            catch
            {
                Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "Failed to create new user.");
                return false;
            }
        }

        //sends message to database
        public bool SendMessage(string username, string description, string to)
        {
            string format = "yyyy-MM-dd HH:mm:ss";
            Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "Sending message from " + username + " to " + to);
            return Executecommand("INSERT INTO Messages(Mid,description,idfrom,idto,datetime) VALUES(" + NewMessageId() + ",'" + description + "'," + GetId(username) + "," + GetId(to) + ",'" + DateTime.Now.ToString(format) + "')");
        }

        //fetches all messages between user and contact
        public List<string> GetMessages(string username, string recieving)
        {
            if (Ingelogd(username))
            {
                try
                {
                    string description;
                    int id;
                    DateTime datetime;
                    List<Message> messages = new List<Message>();
                    List<string> returnmessages = new List<string>();

                    Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "Getting messages from database between " + username + " and " + recieving);

                    SQLiteDataReader reader = FetchData("SELECT * FROM Messages WHERE (idfrom=" + GetId(username) +
                        " AND idto=" + GetId(recieving) + ") " + "OR (idto=" + GetId(username) + " AND idfrom=" + GetId(recieving) + ") ORDER BY datetime");

                    while (reader.Read())
                    {
                        description = (string)reader["description"];        //Because you can't have multiple readers active at the same time,
                        datetime = (DateTime)reader["datetime"];            //the messages are first stored in a list of "Messages" with the 
                        id = (int)reader["idfrom"];                         //data in seperated parts
                        messages.Add(new Message(description, datetime, id));
                    }

                    reader.Close();

                    foreach (Message message in messages)                   //Here the data is converted to a list of strings, so it can be sent to the client
                    {
                        returnmessages.Add(GetUserName(message.senderId) + "`" + message.description + "`" + message.datetime.ToString("HH:mm"));
                    }

                    return returnmessages;
                }
                catch
                {
                    Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "Could not get messages from database");
                    return null;
                }
            }
            return null;
        }

        //fetches all online users and returns list
        public List<string> GetUsers()
        {
            Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "Fetching users from database.");
            List<string> users = new List<string>();

            SQLiteDataReader reader = FetchData("SELECT username FROM users WHERE online=1");   //Typical use of the SQLiteDataReader, it first uses the function: FetchData,
            try                                                                                 //which returns the reader
            {
                while (reader.Read())                                                           //Then, in this while-loop, all data is put into a list of usernames
                {
                    users.Add((string)reader["username"]);
                    Console.WriteLine(reader["username"]);
                }

                reader.Close();                                                                 //The reader needs to be closed, otherwise the whole program collapses
            }
            catch
            {
                Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "Could not find users.");
                return null;                                                                    //Finally, if the read was executed succesfully, the userlist gets returned
            }                                                                                   //otherwise, it gets addressed in the server console and it returns a null-value

            return users;
        }

        //returns id from username
        private int GetId(string username)                   //All functions are username dependent, but the table "Messages"
        {                                                    //does not hold the information of the usernames, only the id's,
            try                                              //so this function returns the username from the given id
            {
                int id;

                SQLiteDataReader reader = FetchData("SELECT id FROM users WHERE username='" + username + "'");
                reader.Read();
                id = (int)reader["id"];
                reader.Close();

                return id;
            }
            catch
            {
                Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "Could not find id from user: " + username);
                return -1;
            }
        }

        //returns username from id
        private string GetUserName(int id)
        {
            string username;

            SQLiteDataReader reader = FetchData("SELECT username FROM users WHERE id='" + id + "'");
            reader.Read();
            username = (string)reader["username"];
            reader.Close();

            return username;
        }

        //returns whether user is logged in
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
        private int NewMessageId ()                                                 //Message and user ID's are just the amount of messages already in the table
        {                                                                           //for example the first message gets id=0, and and the twelfth message gets id=11
            List<string> messages = new List<string>();
            SQLiteDataReader reader = FetchData("SELECT * FROM Messages");

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
            SQLiteDataReader reader = FetchData("SELECT * FROM users");

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
                SQLiteCommand sqlcommand = new SQLiteCommand(query, connection);
                sqlcommand.ExecuteNonQuery();
                return true;
            }
            catch(Exception e)   //all failed queries get addressed in the console, so we can see when and where things go wrong
            {
                Console.WriteLine(e);
                Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "The query: \"" + query + "\" failed to be executed.");
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
                Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "The query: \"" + query + "\" failed to be executed.");
                return null;
            }
        }

        readonly private SQLiteConnection connection;
    }

}