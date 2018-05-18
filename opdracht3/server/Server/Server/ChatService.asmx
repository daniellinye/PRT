<%@ WebService Language="C#" Class="Server.ChatService" %>
using System;
using System.Web.Services;
using Mono.Data.Sqlite;

namespace Server
{
	class ChatService
	{
    SqliteConnection.CreateFile("Users.sqlite");

        
        [WebMethod]
        public string GetTarget()
        {
            return "Hello world";
        }
	}
}
