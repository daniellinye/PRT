<%@ WebService Language="C#" Class="Server.ChatService" %>
using System;
using System.Web.Services;
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

        
        public ChatService()
        {
            SqliteConnection.CreateFile("Users.sqlite");
            SqliteConnection dbconnection = new SqliteConnection("Data Source=Users.sqlite;Version=3;");
            dbconnection.Open();
            maketables(dbconnection);
        }

        private void maketables(SqliteConnection dbconnection)
        {
            string users = "CREATE TABLE users (PRIMARY KEY INT ID, name VARCHAR(20), password VARCHAR(20));";
            string chatbox = "CREATE TABLE chatbox (PRIMARY KEY INT CHATID, INT IDFROM, INT IDTO);";

            executecommand(users, dbconnection);
            executecommand(chatbox, dbconnection);
        }

        public void executecommand(string command, SqliteConnection scon)
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
            ChatService cs = new ChatService();

            return "Hello world";
        }
	}
}
