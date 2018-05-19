<%@ WebService Language="C#" Class="Server.ChatService" %>
using System;
using System.Web.Services;
using System.Net;
using System.Net.Sockets;
using System.Data.SqlClient;
using System.Data.Common;
using System.Data;
using System.IO;
using Server;
using Mono.Data.Sqlite;

namespace Server
{
	class ChatService
	{


        [WebMethod]
        string startup()
        {
            const int port = 8080;
            const string ip = "127.0.0.1";


            //TODO:try without buffer?
            //start listening at 
            //port 8080
            IPAddress iaddress = IPAddress.Parse(ip);
            TcpListener listen = new TcpListener(iaddress, port);
            Console.WriteLine("Starting");
            listen.Start();

            //connect client
            TcpClient tclient = listen.AcceptTcpClient();

            //fetch data
            NetworkStream nstream = tclient.GetStream();

            string input = Read(nstream);

            Console.WriteLine("Recieved" + input);

            StreamWrite(input, "None", nstream);
            //ping back

            tclient.Close();
            listen.Stop();
            return "it worked?";
        }

        public String Read(NetworkStream stream)
        {

            byte[] myReadBuffer = new byte[1024];
            String responseData = String.Empty;
            Int32 bytes = stream.Read(myReadBuffer, 0, myReadBuffer.Length);
            responseData = System.Text.Encoding.ASCII.GetString(myReadBuffer, 0, bytes);
            //Make it so I can actually
            //Console.WriteLine(responseData);
            return responseData;
        }

        public String StreamWrite(String input, String status, NetworkStream stream)
        {
            Byte[] login = System.Text.Encoding.ASCII.GetBytes(input);
            stream.Write(login, 0, login.Length);
            Console.WriteLine(input);
            Console.WriteLine(status);
            return input;
        }

        public static void Say(String input, NetworkStream stream)
        {
            string annstring = input;
            Byte[] announce = System.Text.Encoding.ASCII.GetBytes(annstring);
            stream.Write(announce, 0, announce.Length);
        }


        public ChatService()
        {
            SqliteConnection.CreateFile("Users.sqlite");
            SqliteConnection dbconnection = new SqliteConnection("Data Source=Users.sqlite;Version=3;");
            dbconnection.Open();
            string users = "CREATE TABLE users (id INTEGER , name VARCHAR(20), password VARCHAR(20), PRIMARY KEY (id));";
            string chatbox = "CREATE TABLE chatbox (chatid INTEGER, idfrom INTEGER, idto INTEGER, chatroom INTEGER,"
            +"message VARCHAR(80) , PRIMARY KEY (chatid, chatroom)"
            + "FOREIGN KEY idfrom REFERENCES users, FOREIGN KEY idto REFERENCES users);";

            executecommand(users, dbconnection);
            executecommand(chatbox, dbconnection);
        }

        void executecommand(string command, SqliteConnection scon)
        {
            SqliteCommand sqlcommand = new SqliteCommand(command, scon);
            sqlcommand.ExecuteNonQuery();
        }


        public object getTables(SqliteConnection dbconnection, string selectargs)
        {
            SqliteCommand sqlcommand = new SqliteCommand();
            sqlcommand.CommandText = selectargs;
            sqlcommand.CommandType = CommandType.Text;
            sqlcommand.Connection = dbconnection;

            return sqlcommand.ExecuteReader();
        }


        [WebMethod]
        public string GetTarget()
        {
            

            return "Hello world";
        }
	}
}
