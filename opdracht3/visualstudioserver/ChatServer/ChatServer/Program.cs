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
    public class Program
    {
        //parseclass
        ParseFunctions pf = new ParseFunctions();

        /*
         explanation table of between server and client:
         if ping
         write pong
         if login
         add to userlist
         if logout
         remove from userlist
         if message
         add to messagelist
         if getuser
         returns userlist
         if getmessage
         returns messagelist
             */


        static void Main(string[] args)
        {
            SocketListener sl = new SocketListener();
            Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "Initializing SocketListener");
            sl.NetSocketListener(8081, "127.0.0.1");
            Console.WriteLine("SERVER ROOM IS ON FIRE");
            sl.NetSocketListener(8081, "127.0.0.1");
            Console.WriteLine("SERVER ROOM IS ON FIRE");

        }


    } // class Program
}
