<%@ WebService Language="C#" Class="Server.ChatService" %>
using System;
using System.Web.Services;

namespace Server
{
	class ChatService
	{
        [WebMethod]
        public string GetTarget()
        {
            return "Hello world";
        }
	}
}
