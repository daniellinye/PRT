using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FormAppClient
{
    static class Program
    {


        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new LoginWindow());
        }
    }

    public static class Statistics
    {
        public static NetFunctions _nf = new NetFunctions();
        public static string[] _onlineusers;
        public static List<string[]> _usermessages;

        public static string[] onlineusers
        {
            get { return _onlineusers; }
            set { _onlineusers = value; }
        }

        public static string[] usermessages
        {
            get { return _onlineusers; }
            set { _onlineusers = value; }
        }

        public static NetFunctions nf
        {
            get { return _nf; }
        }
    }


    public class NetFunctions
    {
        //To be setuped when pinging server
        public int id;
        private string hashcode;
        private StringBuilder commands;

        public NetFunctions()
        {
            commands = new StringBuilder();
        }


        public void Login(NetworkStream stream, string username, string password)
        {
            AddCommand("LOGIN", new string[] { username, password });
        }

        public void Logout( string username, string hashcode)
        {
            AddCommand("LOGOUT", new string[] { username, hashcode });
        }

        public void Message(string username, string recipient)
        {

            AddCommand("MESSAGE", new string[] { username, recipient, hashcode });

        }

        public void Update(string username, string recipient)
        {
            AddCommand("UPDATE", new string[] { username, recipient, hashcode });
        }

        public void Online()
        {
            AddCommand("ONLINE", new string[] { });
        }

        public void Register(string username, string password)
        {
            AddCommand("REGISTER", new string[] { username, password });
        }

        public void AddCommand(string command, string[] args)
        {
            commands.Append(command);

            foreach (string arg in args)
            {
                commands.Append("#");
                commands.Append(arg);
            }
            commands.Append("|");
        }

        public void UpdateChat(string args)
        {
            //TODO: wait for database parser server side
        }

        public void UpdateUsers(string args)
        {
            string[] temp = args.Split('%');
            Statistics.onlineusers = new string[temp.Length];
            for(int i = 0; i < temp.Length; i++)
            {
                Statistics.onlineusers[i] = temp[i];
            }
        }

        public StringBuilder Parser(string input)
        {
            string[] lines = input.Split('|');
            StringBuilder builder = new StringBuilder();
            foreach(string line in lines)
            {
                string[] command = line.Split('#');
                switch(command[0])
                {
                    case "RESPONSECODE":
                        //Responsecodes are pretty much just for debugging such that I can see console outputs,
                        //but sometimes they're to communicate to the user
                        builder.Append(command[1]);
                        builder.Append('$');
                        break;
                    case "LOGOUT":
                        //TODO: implement update that logout
                        //LoginResponse(command[1]);
                        break;
                    case "HASHCODE":
                        //TODO:
                        //used for login, just check after wether you have a hashcode that isn't null
                        hashcode = command[1];
                        break;
                    case "UPDATE":
                        //TODO: actually update the chat window with proper parsing
                        //Chatwindow(command[1]);
                        break;
                    case "USERS":
                        UpdateUsers(command[1]);
                        break;
                    default:
                        Console.WriteLine("ERROR: COMMAND " + command[0] + " EITHER NOT IMPLEMENTEDD OR FOUND!");
                        break;
                }
            }
            return builder;
        }

        //ALWAYS USE THIS COMMAND IN ORDER TO PREVENT DEADLOCK
        //except pingpong, pingpong is always fine
        public StringBuilder SendCommands(NetworkStream stream)
        {
            StringBuilder returnvalues = new StringBuilder();

            commands.Append("$<EOF>");
            string[] sending = commands.ToString().Split('|');
            foreach(string strings in sending)
            {
                if (strings.IndexOf("<EOF>") == -1)
                    StreamWrite(strings + "|", stream);
                else
                    StreamWrite(strings, stream);
            }
            //clear commands after sending them
            commands.Clear();

            while(returnvalues.ToString().IndexOf("<EOF>") != -1)
            {
                returnvalues.Append(Read(stream));
            }
            return returnvalues;
        }

        public string Read(NetworkStream stream)
        {
            byte[] myReadBuffer = new byte[1024];
            String responseData = String.Empty;
            Int32 bytes = stream.Read(myReadBuffer, 0, myReadBuffer.Length);
            responseData = System.Text.Encoding.ASCII.GetString(myReadBuffer, 0, bytes);
            return responseData;
        }

        public string StreamWrite(String input, NetworkStream stream)
        {
            Byte[] login = System.Text.Encoding.ASCII.GetBytes(input);
            stream.Write(login, 0, login.Length);
            Console.WriteLine(input);
            return input;
        }

    }
}

/*
 TODO:
 - Make Chatwindow and LoginWindow interactable
    = registerwindow
    = loginwindow
 - Implement commands:
    = Login  = transitions screen when loginrequest is succesfull
    = Update = returns an update from database from user and messages, parsing is stated in server
    = Online = same as above except online users
 - multithread the following:
    = chatwindow and interactables (aka adding commands)
    = sendcommand on a 5 second timeloop sleep
 - write design about the api; describe the parsing and sockets. Meaning that every instance of a connection gets its' own socket
   whilst the parsing can just be in it's own documentation. I've written a mockup on a README.txt (dunno which one anymore).
   Just work that out and we should be fine.
   Also it's a factory method on the backend of the server side, actually planned up ahead.
   And for the server/client it's publish/subscribe (qua softwaredesign)

    README:
    - commands are added to a list when you use them, then you send it to the server manually via SendCommands
    - happens on a 5-second timeloop, except for the login and register windows

     */