﻿using System;
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
        public string sendname;
        public Message(string desc, DateTime date, string name)
        {
            description = desc;
            datetime = date;
            sendname = name;
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

                Executecommand("INSERT INTO users(Id,username,password,online) VALUES(0,'Robert','wachtwoord',0)");
                Executecommand("INSERT INTO users(Id,username,password,online) VALUES(1,'Piet','wachtwoord',1)");
                Executecommand("INSERT INTO users(Id,username,password,online) VALUES(2,'Hein','wachtwoord',1)");
                
                Console.WriteLine(DateTime.Now.ToString("[hh:mm:ss] ") + "Connection Successful");
            }
            catch
            {
                Console.WriteLine(DateTime.Now.ToString("[hh:mm:ss] ") + "Connection Unsuccesfull");
            }
        }

        //executes a function on the database and returns values
        public bool ExecuteFunction(string function, string args)
        {
            //TODO:
            //add basic functionalities to login, getmessages
            //sendmessages, getuser, sendmessages and login
            
            LogIn("Robert", "wachtwoord");

            int buddyId = 1;
            SendMessage(buddyId, "Hallo Piet");
            GetMessages(buddyId);

            switch (function)
            {
                case "Login":
                    string[] parser = args.Split('.');
                    Console.WriteLine("Loggin in" + args);
                    return LogIn(parser[0], parser[1]);
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
                Executecommand("UPDATE users SET online=1 WHERE id=" + userId);
            }
            catch
            {
                Console.WriteLine("Log in attempt failed.");
            }
            return false;

        }

        private void SendMessage(int toId, string description)
        {
            try
            {
                string format = "yyyy-MM-dd HH:mm:ss";
                Executecommand("INSERT INTO Messages(Mid,description,idfrom,idto,datetime) VALUES(1,'" + description + "'," + userId + "," + toId + ",'" + DateTime.Now.ToString(format) + "')");
            }
            catch
            {
                Console.WriteLine("Failed to send message.");
            }
        }

        private List<Message> GetMessages(int buddyId)
        {
            if (ingelogd)
            {
                string description, name;
                SqlDataReader namereader;
                DateTime datetime;
                List<Message> messages = new List<Message>();

                SqlDataReader reader = FetchData("SELECT * FROM Messages WHERE (idfrom=" + userId +
                    " AND idto=" + buddyId + ")" + " OR (idto=" + userId + " AND idfrom=" + buddyId + ") ORDER BY datetime");

                if(reader != null)
                {
                    namereader = FetchData("SELECT username FROM users WHERE id=" + reader["idfrom"]);
                    description = (string)reader["description"];
                    datetime = (DateTime)reader["datetime"];
                    while(namereader != null && namereader.Read())

                    while (reader.Read())
                    {
                        namereader = FetchData("SELECT username FROM users WHERE id=" + reader["idfrom"]);
                        description = (string)reader["description"];
                        datetime = (DateTime)reader["datetime"];
                        while (reader.Read())
                        {
                            name = (string)reader["username"];
                            Console.WriteLine(name);
                        }
                        messages.Add(new Message(description, datetime, "hallo"));
                    }

                    Console.WriteLine("[" + messages[0].datetime + "]" + messages[0].description);
                }


                return messages;
            }
            return null;
        }

        private void Executecommand(string query)
        {
            try
            {
                SqlCommand sqlcommand = new SqlCommand(query, connection);
                sqlcommand.ExecuteNonQuery();
            }
            catch
            {
                Console.WriteLine(DateTime.Now.ToString("[hh:mm:ss] ") + "The query: \"" + query + "\" failed to be executed.");
            }
        }


        private SqlDataReader FetchData(string query)
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