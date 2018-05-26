﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Data.SqlClient;
using System.Data.SqlTypes;
using System.Net;
using System.Threading;


namespace ChatServer
{
    public class Program
    {

        /*
         explanation login and pingpong:
         if ping
         write pong
         if login
         add to userlist
         if logout
         remove from userlist
         if message
         add to messagelist
             */

        static void Main(string[] args)
        {
            Program p = new Program();
            Console.WriteLine("did stuff");
            p.Startup();

        }

        public void Startup()
        {
            const int port = 8080;
            const string ip = "127.0.0.1";

            //start listening at 
            //port 8080

            ConnectionFunctions cf = new ConnectionFunctions();
            IPAddress iaddress = IPAddress.Parse(ip);
            TcpListener listen = new TcpListener(iaddress, port);
            Console.WriteLine("Starting");
            listen.Start();

            DatabaseFunctions df = new DatabaseFunctions();

            df.LogIn("Robert","wachtwoord");


            //connect client
            TcpClient client = listen.AcceptTcpClient();

            //fetch data
            NetworkStream stream = client.GetStream();

            //parseclass
            ParseFunctions pf = new ParseFunctions();

            try
            {
                while (true)
                {
                    string input = pf.Read(stream);
                    Console.WriteLine(input);

                    if(input != String.Empty)
                    {
                        //TODO: make multithread when someone actually has logged in
                        pf.Parser(input, stream);
                    }
                    else
                    {
                        client.Close();
                        listen.Stop();
                        Startup();
                    }

                }
            }
            catch(Exception e)
            {
                Console.WriteLine(e);
            }
            finally
            {

                client.Close();
                listen.Stop();
            }

            Console.WriteLine("Reading Stream");

        }

        //multithreader for new users
        public void CheckNewUsers(TcpListener listener, ConnectionFunctions cf)
        {

        }
        

        public static void Say(String input, NetworkStream stream)
        {
            string annstring = input;
            Byte[] announce = System.Text.Encoding.ASCII.GetBytes(annstring);
            stream.Write(announce, 0, announce.Length);
        }

    } // class Program

    //is a stuct such that we can give users variables whilst online
    public class TcpUsers : TcpClient
    {
        TcpClient client;
        String name;

        public TcpUsers(TcpClient listener, String newname)
        {
            name = newname;
            client = listener;
        }

        public String ReturnName()
        {
            return name;
        }
    }

    public class ConnectionFunctions
    {
        public List<TcpUsers> clients = new List<TcpUsers>();

        public ConnectionFunctions() { }

        //adds new client if the user is not logged in yet
        public void LoginUser(TcpClient client, String name)
        {
            foreach(TcpClient c in clients)
            {
                if(c.Equals(client))
                {
                    return;
                }
            }
            Console.WriteLine("User: " + name  + "Logged in");
            clients.Add(new TcpUsers(client, name));
        }

        public void LogoutUser(String name)
        {
            foreach(TcpUsers c in clients)
            {
                if(c.ReturnName() == name)
                {
                    clients.Remove(c);
                    return;
                }
            }
            Console.WriteLine("Element was not found in list");
        }


    }

    class ParseFunctions
    {
        ConnectionFunctions cf;
        public ParseFunctions()
        {
            cf = new ConnectionFunctions();
        }

        public void Parser(String input, NetworkStream stream)
        {

            //TODO: REMINDER
            //whenever a user is logged in, add the current connection to the clients of ConnectionFunctions
            string[] parser = input.Split('.');
            switch(parser[0])
            {
                case "Ping":
                    StreamWrite("Pong", stream);
                    break;
                //standardthing
                default:
                    Console.WriteLine("Command " + parser[0] + " was not implemented");
                    StreamWrite("Error:001, command not found", stream);
                    break;
            }
        }

        //reads rawdata from the newworkstream :D
        public String Read(NetworkStream stream)
        {
            byte[] myReadBuffer = new byte[1024];
            String responseData = String.Empty;
            Int32 bytes = stream.Read(myReadBuffer, 0, myReadBuffer.Length);
            responseData = System.Text.Encoding.ASCII.GetString(myReadBuffer, 0, bytes);
            return responseData;
        }

        //writes rawdata to the newtworkstream :D
        public String StreamWrite(String input, NetworkStream stream)
        {
            Byte[] login = System.Text.Encoding.ASCII.GetBytes(input);
            stream.Write(login, 0, login.Length);
            Console.WriteLine(input);
            return input;
        }

        //format has to be: "username:password"
        public bool Login(String input)
        {
            String[] parser = input.Split(':');
            string username = parser[0];
            string password = parser[1];
            //TODO: throw check to database

            return false;
        }


    }

    class DatabaseFunctions
    {
        public DatabaseFunctions()
        {

        }

        public void LogIn(string username, string password)
        {

            try
            {
                //Is now hardcoded but should be an online service
                //service is not available yet, so this is hardcoded
                //for testing: change the Path after AttachDbFilename=
                using (SqlConnection connection = new SqlConnection("Data Source=(LocalDB)\\MSSQLLocalDB;AttachDbFilename=D:\\Studie\\PRT\\opdracht3\\visualstudioserver\\ChatServer\\ChatServer\\users.mdf;Integrated Security=True"))
                {
                    Console.WriteLine("Opening connection");
                    connection.Open();
                    Executecommand(connection, "DELETE FROM users");
                    Executecommand(connection, "INSERT INTO users (name,password) VALUES ('" + username + "','" + password + "')");
                    
                    SqlDataReader reader = GetTables(connection, "SELECT * FROM users");

                    while (reader.Read())
                    {
                        Console.WriteLine(reader["name"].ToString());
                    }
                }
                Console.WriteLine("Connection Successful");
            }
            catch
            {
                Console.WriteLine("Connection Unsuccesfull");
            }

        }

        public void Executecommand(SqlConnection dbconnection, string query)
        {
            try
            {
                SqlCommand sqlcommand = new SqlCommand(query, dbconnection);
                sqlcommand.ExecuteNonQuery();
            }
            catch
            {
                Console.WriteLine(query);
            }
        }


        public SqlDataReader GetTables(SqlConnection dbconnection, string query)
        {
            SqlCommand sqlcommand = new SqlCommand();
            sqlcommand.CommandText = query;
            sqlcommand.Connection = dbconnection;

            return sqlcommand.ExecuteReader();
        }
    }


}
