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
        void startup()
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
            byte[] buffer = new byte[tclient.RecieveBufferSize];

            //read stream
            int bytesread = nstream.Read(buffer, 0, tclient.RecieveBufferSize);

            //convert
            string data = Encoding.ASCII.GetString(buffer, 0, bytesread);
            Console.Writeline("Recieved" + data);

            //ping back
            nstream.Write(buffer, 0, bytesread);
            tclient.close();
            listen.Stop();
        }


        /*
        public ChatService()
        {
            SqliteConnection.CreateFile("Users.sqlite");
            SqliteConnection dbconnection = new SqliteConnection("Data Source=Users.sqlite;Version=3;");
            dbconnection.Open();
            string users = "CREATE TABLE users (PRIMARY KEY INT ID, name VARCHAR(20), password VARCHAR(20));";
            string chatbox = "CREATE TABLE chatbox (PRIMARY KEY INT CHATID, INT IDFROM, INT IDTO);";

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

        */
        [WebMethod]
        public string GetTarget()
        {
            

            return "Hello world";
        }
	}
}
