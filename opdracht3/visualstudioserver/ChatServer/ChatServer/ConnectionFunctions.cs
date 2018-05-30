using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Net;
using System.Threading;
using ChatServer;


namespace ChatServer
{

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
            int id = clients.Count;
            foreach (TcpUsers c in clients)
            {
                if (c.Equals(client))
                {
                    Console.WriteLine("User " + name + " is already logged in");
                    id = c.ReturnId();
                }
            }
            Console.WriteLine("User: " + name + " Logged in");
            clients.Add(new TcpUsers(client, name, id));
        }

        public void LogoutUser(String name, int id)
        {
            foreach (TcpUsers c in clients)
            {
                if (c.ReturnName() == name && c.ReturnId() == id)
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
            //TODO: implement
        }

        public TcpUsers GetMostRecent()
        {
            return clients[clients.Count - 1];
        }

        public TcpUsers GetName(int id)
        {
            return clients[id];
        }

        public TcpUsers GetClient(string name)
        {
            foreach (TcpUsers c in clients)
            {
                if(c.ReturnName() == name)
                {
                    return c;
                }
            }
            return null;
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
            Console.WriteLine(input);

            switch (command[0])
            {
                case "Ping":
                    StreamWrite("Pong", stream);
                    break;
                case "Login":
                    string[] lparser = command[1].Split('.');
                    string username = lparser[0];
                    string password = lparser[1];
                    Console.WriteLine(username + "login attempt.");
                    if(Login(username, password, client))
                    {
                        cf.LoginUser(client, username);
                        int id = cf.GetMostRecent().ReturnId();
                        StreamWrite("Login successfull id given:" + id, stream);
                        return true;
                    }
                    break;
                //standardthing
                case "Message":

                    //TODO: give id a proper way to identify between clients
                    string[] uparser = command[1].Split(',');
                    string[] mparser = uparser[1].Split('.');
                    string user = uparser[0];
                    string recipient = mparser[0];
                    string message = mparser[1];
                    Message(user, recipient, message, client);
                    break;
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

        //format has to be: "username.password"
        public bool Login(string username, string password, TcpClient client)
        {
            //TODO: throw check to database
            //that returns null if not found
            if (df.ExecuteFunction("Login", username + "." + password))
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

        public void Message(string username, string password, string message, TcpClient client)
        {
            //TODO
            //PING TO OTHER CLIENTS

            StreamWrite("Method is not implemented yet", client.GetStream());
            //PING OTHER USERS

            //TODO
            //ADD TO DATABASE
        }

        public string LoadMessages(string username, string password, string otheruser)
        {
            //TODO
            //PING TO DATABASE TO RETRIEVE
            //MESSAGES

            return null;
        }


    }

}
