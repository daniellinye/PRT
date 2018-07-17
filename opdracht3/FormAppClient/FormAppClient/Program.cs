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


    public class NetFunctions
    {
        //To be setuped when pinging server
        public int id;
        StringBuilder commands;

        public NetFunctions()
        {

        }


        public void Login(NetworkStream stream, string username, string password)
        {
            try
            {
                AddCommand("LOGIN", new string[] { username, password });


            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }

        public void Logout(NetworkStream stream, string username, string hashcode)
        {
            try
            {
                AddCommand("LOGOUT", new string[] { username, hashcode });
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }

        public void Message(NetworkStream stream, string username, string recipient, string hashcode)
        {
            try
            {
                AddCommand("MESSAGE", new string[] { username, recipient, hashcode });
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }

        public void Update(NetworkStream stream, string username, string recipient, string hashcode)
        {
            try
            {
                AddCommand("UPDATE", new string[] { username, recipient, hashcode });
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }

        public List<string> GetUsers(NetworkStream stream)
        {
            List<string> users = new List<string>();
            StreamWrite("GetUsers", stream);
            string reading = Read(stream);

            while (reading != "")
            {
                users.Add(reading);
            }

            return users;
        }

        public void AddCommand(string command, string[] args)
        {
            commands.Append(command);
            commands.Append(":");

            foreach (string arg in args)
            {
                commands.Append("#");
                commands.Append(arg);
            }
            commands.Append("|");
        }

        //ALWAYS USE THIS COMMAND IN ORDER TO PREVENT DEADLOCK
        //except pingpong, pingpong is always fine
        public string SendCommands(NetworkStream stream)
        {
            commands.Append("|<EOF>");
            StreamWrite(commands.ToString(), stream);
            return Read(stream);
        }


        public string Read(NetworkStream stream)
        {

            byte[] myReadBuffer = new byte[1024];
            String responseData = String.Empty;
            Int32 bytes = stream.Read(myReadBuffer, 0, myReadBuffer.Length);
            responseData = System.Text.Encoding.ASCII.GetString(myReadBuffer, 0, bytes);
            //Make it so I can actually
            //Console.WriteLine(responseData);
            return responseData;
        }

        public string GetMessages(NetworkStream stream)
        {
            StreamWrite("GetMessages", stream);
            return Read(stream);

        }

        public string StreamWrite(String input, NetworkStream stream)
        {
            Byte[] login = System.Text.Encoding.ASCII.GetBytes(input);
            stream.Write(login, 0, login.Length);
            Console.WriteLine(input);
            return input;
        }

        public static void Say(String input, NetworkStream stream)
        {
            string annstring = input;
            Byte[] announce = System.Text.Encoding.ASCII.GetBytes(annstring);
            stream.Write(announce, 0, announce.Length);
        }

    }
}
