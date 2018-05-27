using System;
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

        private bool newuser;

        static void Main(string[] args)
        {
            Program p = new Program();
            Console.WriteLine("did stuff");
            Thread th = new Thread(p.Startup);
            th.Start();
        }

        public void Startup()
        {
            newuser = false;
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

            Thread t = new Thread ( () => LoginRequest(client, listen));
            if(newuser)
            {
                Thread listening = new Thread ( () => ListenToNewUser(client, listen));
                listening.Start();
            }
            t.Start();

        }

        //handles loginrequests
        public void LoginRequest(TcpClient client, TcpListener listen)
        {
            //parseclass
            ParseFunctions pf = new ParseFunctions();
            try
            {
                while (true)
                {
                    string input = pf.Read(client.GetStream());
                    Console.WriteLine(input);

                    if (input != String.Empty)
                    {
                        //TODO: make multithread when someone actually has logged in
                        if(pf.Parser(input, client))
                        {
                            //HERE PING BACK NEW MULTITHREAD
                            newuser = true;
                        }
                        else
                        {
                            pf.StreamWrite("Invalid login", client.GetStream());
                        }
                    }
                    else
                    {
                        client.Close();
                        listen.Stop();
                        Startup();
                    }

                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
            finally
            {
                client.Close();
                listen.Stop();
                Startup();
            }
        }

        //multithread to listen to the current users
        public void ListenToNewUser(TcpClient client, TcpListener listen)
        {
            //parseclass
            ParseFunctions pf = new ParseFunctions();
            try
            {
                while (true)
                {
                    string input = pf.Read(client.GetStream());
                    Console.WriteLine(input);

                    if (input != String.Empty)
                    {
                        //TODO: make multithread when someone actually has logged in
                        pf.Parser(input, client);
                    }
                    else
                    {
                        client.Close();
                        listen.Stop();
                        Startup();
                    }

                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                Console.WriteLine("User was forcibly logged out.");
            }
            finally
            {
                //TODO: INSERT LOGOUT FOR CURRENT USER
                client.Close();
                listen.Stop();
            }
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
        int id;

        public TcpUsers(TcpClient listener, String newname, int nid)
        {
            name = newname;
            client = listener;
            id = nid;
        }

        public String ReturnName()
        {
            return name;
        }

        public int ReturnId()
        {
            return id;
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
                    Console.WriteLine("User " + name + " is already logged in");
                    return;
                }
            }
            Console.WriteLine("User: " + name  + " Logged in");
            clients.Add(new TcpUsers(client, name, clients.Count));
        }

        public void LogoutUser(String name, int id)
        {
            foreach(TcpUsers c in clients)
            {
                if(c.ReturnName() == name && c.ReturnId() == id)
                {
                    c.Close();
                    clients.Remove(c);
                    return;
                }
            }
            Console.WriteLine("Error 404:Element was not found in list");
        }

        //pings other clients depended on the messagesender
        public void Ping(String message, int id)
        {

        }

    }

    class ParseFunctions
    {
        ConnectionFunctions cf;
        DatabaseFunctions df;
        public ParseFunctions()
        {
            cf = new ConnectionFunctions();
            df = new DatabaseFunctions();
        }

        public bool Parser(String input, TcpClient client)
        {
            NetworkStream stream = client.GetStream();
            //TODO: REMINDER
            //whenever a user is logged in, add the current connection to the clients of ConnectionFunctions

            String[] command = input.Split(':');

            switch (command[0])
            {
                case "Ping":
                    StreamWrite("Pong", stream);
                    break;
                case "Login":
                    string[] parser = command[1].Split('.');
                    string username = parser[0];
                    string password = parser[1];
                    return Login(username, password, client);
                //standardthing
                default:
                    Console.WriteLine("Command " + command[0] + " was not implemented");
                    StreamWrite("Error:001, command not found", stream);
                    break;
            }
            return false;
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
        public bool Login(string username, string password, TcpClient client)
        {
            //TODO: throw check to database
            //that returns null if not found
            if (df.ExecuteFunction("Login", username + "." + password) != null)
            {
                cf.LoginUser(client, username);
                return true;
            }

            return false;
        }

        public bool Logout(string username, string password, TcpClient client)
        {

            return false;
        }

        public void Message(string username, string password, string message)
        {
            //TODO
            //PING TO OTHER CLIENTS

            //TODO
            //ADD TO DATABASE
        }

        public string LoadMessages(string username, string password, string otheruser)
        {
            //TODO
            //PING TO DATABASE TO RETRIEVE
            //MESSAGES
            string messages;

            return null;
        }


    }

    class DatabaseFunctions
    {
        public DatabaseFunctions()
        {

        }

        //executes a function on the database and returns values
        public string ExecuteFunction(string function, string args)
        {
            //TODO:
            //add basic functionalities to login, getmessages
            //sendmessages, getuser, sendmessages and login
            switch(function)
            {
                default:
                    Console.WriteLine("DatabaseFunction: " + function + " not recognized or implemented.");
                    break;
            }

            return null;
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
