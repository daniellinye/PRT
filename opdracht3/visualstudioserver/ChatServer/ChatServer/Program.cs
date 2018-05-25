﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Data.SqlClient;
using System.Data.SqlTypes;
using System.Net;


namespace ChatServer
{
    class Program
    {
        static void Main(string[] args)
        {
            Program p = new Program();
            Console.WriteLine("did stuff");
            p.Startup();
        }

        public string Startup()
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


            //connect client
            TcpClient tclient = listen.AcceptTcpClient();

            //fetch data
            NetworkStream nstream = tclient.GetStream();

            Console.WriteLine("Reading Stream");
            string input = cf.Read(nstream);

            Console.WriteLine(input);

            cf.StreamWrite(input, "None", nstream);
            //ping back



            tclient.Close();
            listen.Stop();
            return "it worked?";
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


        public void ChatService()
        {
            /*using (SqlConnection connection = new SqlConnection("Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=D:\Github\PRT\opdracht3\visualstudioserver\ChatServer\ChatServer\users.mdf;Integrated Security=True"))
            {
                Console.WriteLine("Opening connection");
                connection.Open();
            }
            Console.WriteLine();
            */
        }

        public void Executecommand(string command, SqlConnection scon)
        {
            SqlCommand sqlcommand = new SqlCommand(command, scon);
            sqlcommand.ExecuteNonQuery();
        }


        public object GetTables(SqlConnection dbconnection, string selectargs)
        {
            SqlCommand sqlcommand = new SqlCommand();
            sqlcommand.CommandText = selectargs;
            sqlcommand.Connection = dbconnection;

            return sqlcommand.ExecuteReader();
        }

    } // class Program

    public class ConnectionFunctions
    {
        public List<TcpClient> clients = new List<TcpClient>();

        public ConnectionFunctions() { }

        //adds new client if the user is not logged in yet
        public void LoginUser(TcpClient client)
        {
            foreach(TcpClient c in clients)
            {
                if(c.Equals(client))
                {
                    return;
                }
            }
            Console.WriteLine("User: " + client.GetStream() + "Logged in");
            clients.Add(client);
        }

        public void LogoutUser(TcpClient client)
        {
            foreach(TcpClient c in clients)
            {
                if(c.Equals(client))
                {
                    clients.Remove(c);
                    return;
                }
            }
            Console.WriteLine("Element was not found in list");
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
        public String StreamWrite(String input, String status, NetworkStream stream)
        {
            Byte[] login = System.Text.Encoding.ASCII.GetBytes(input);
            stream.Write(login, 0, login.Length);
            Console.WriteLine(input);
            Console.WriteLine(status);
            return input;
        }
    }

}
