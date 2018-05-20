using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Text;
using System.Net.Sockets;
//got bug in pinging back twitch server FIXED
namespace WindowsFormsApp1
{
    static class Start
    {
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            Int32 port = 6667;
            TcpClient client = new TcpClient("irc.twitch.tv", port);

            NetworkStream stream = client.GetStream();

            BotFunctions commands = new BotFunctions(stream);

            try
            {
                //input = string channelname
                commands.Connect("daniellinye");
            }
            catch(Exception)
            {
                Console.WriteLine("Something went wrong on init");
            }

            stream.Close();
            client.Close();
            Console.WriteLine("\n Press Enter to continue...");
            Console.Read();
        }

    }

    public class BotFunctions
    {
        NetworkStream stream;
        public BotFunctions(NetworkStream _stream)
        {
            this.stream = _stream;
        }

        public void Connect(String channel)
        {
            Int32 port = 6667;
            TcpClient client = new TcpClient("irc.twitch.tv", port);
            // Get a client stream for reading and writing.
            NetworkStream stream = client.GetStream();

            //Startup stream functions
            Startup(stream, channel);

            // Initialize writer
            Writefunctions wf = new Writefunctions(@"D:\stream", channel);

            //
            CommandFunctions cf = new CommandFunctions();

            while (true)
            {
                String message = PingBack(ReadComment(stream), stream);

                if (message != String.Empty)
                {
                    cf.EnterCommand(message, channel, stream);
                    wf.Write(message);
                }
            }
        }

        public void Startup(NetworkStream stream, string channel)
        {
            // Send the message to the connected TcpServer. 
            StreamWrite("PASS oauth:51uhqh960gez7qn6uijpy5j8urmm9d\r\nNICK FrankTheForestDragon\r\n", "Sent login.\r\n", stream);

            // Receive the TcpServer.response.
            Read(stream);

            // send message to join channel
            StreamWrite("JOIN " + "#" + channel + "\r\n", "Sent channel join.\r\n", stream);

            // Get confirmation for joining channel
            Read(stream);

            // Retrieve username list
            Read(stream);

            // PMs the channel to announce that it's joined and listening
            Console.WriteLine("Sending Welcome message\r\n");
            Say("PRIVMSG #" + channel + " :" + "Hi I am Frank, a forest dragon and helper of this channel.\r\n", stream);

            // Lets you know its working
            Console.WriteLine("TWITCH CHAT HAS BEGUN.\r\n");
            Console.WriteLine("BE CAREFUL.\r\n");
        }

        public String ReadComment(NetworkStream stream)
        {

            string message = string.Empty;

            do
            {
                try { message = Read(stream).Trim('\n').Trim('\r'); }
                catch (Exception)
                {
                    Console.WriteLine("Rip buffer");
                }

            }
            while (stream.DataAvailable);
            //print the message
            return message;
        }

        private string PingBack(String input, NetworkStream stream)
        {
            switch(input)
            {
                //every 5 minutes server will ping to check

                case "PING :tmi.twitch.tv":
                    try
                    {
                        Say("PONG :tmi.twitch.tv\r\n", stream);
                        Console.WriteLine("Ponged back");
                    }
                    catch(Exception)
                    {
                        Console.WriteLine("Missed pong?");
                    }
                    return string.Empty;
                case "\r\n":
                    return string.Empty;
                case "":
                    return string.Empty;
                default:
                    try
                    {
                        string parser = input;
                        string[] message = parser.Split(':');
                        string[] preamble = message[1].Split('#');
                        string user = preamble[1];
                        string pm = message[2];

                        //private message
                        return user.TrimEnd(' ') + ":" + pm;
                    }
                    catch(Exception)
                    {
                        Console.WriteLine("Something went wrong filtering");
                        return string.Empty;
                    }
            }
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

    }

    class Writefunctions
    {
        public string path;
        FileStream filestream;
        StreamWriter streamwriter;
        public Writefunctions(string dir, string channelname)
        {
            try
            {
                //make new path for the session
                string newpath = System.IO.Path.Combine(dir, string.Format("{0}", DateTime.Now.ToString().Replace(":", ".").Replace("/", ".")) + " " + channelname);
                Console.WriteLine(newpath);
                System.IO.Directory.CreateDirectory(newpath);
                newpath = System.IO.Path.Combine(newpath, "chat.txt");
                path = newpath;
                filestream = new FileStream(newpath, FileMode.OpenOrCreate);
                streamwriter = new StreamWriter(filestream);
                streamwriter.Close();
                filestream.Close();

            }
            catch(Exception e)
            {
                Console.WriteLine("Rip on filewriterinit");
                Console.WriteLine(e);
            }
        }

        public void Write(string input)
        {
            try
            {
                System.IO.File.WriteAllText(path, input);
                Console.WriteLine(input);
            }
            catch(Exception e)
            {
                Console.WriteLine(e);
                Console.WriteLine("Didn't write");
            }

        }
    }

    public class CommandFunctions
        //checks what kind of command has been given after #
    {
        DateTime time = DateTime.Now;
        private List<Message> rafflelist = new List<Message>();
        Random r = new Random();
        private bool raffle = false;
        //message is split by a ':'
        public CommandFunctions() { }

        public void EnterCommand(string message, string channelname, NetworkStream stream)
        {
            //temp[0] = user, temp[1] = message
            //commands in the chat are done with: ##
            string[] temp = message.Split(':');
            if(temp[1][0].Equals('#'))
            {
                Filter(temp[1].TrimStart('#').Trim(' '), temp[0].Trim(' '), message,  channelname, stream);
            }
        }

        public void Filter(string command, string user, string message, string channelname, NetworkStream stream)
        {
            try
            {
                //separate the command prefix and actual thing
                string[] separator = command.Split('.');
                string filter = message.Substring(6, message.Length-6);
                switch(separator[0])
                {
                    case "raffle":
                        if (user.Equals("daniellinye") || user.Equals(channelname))
                        {
                            AdminRCommands(separator[1], time);
                        }
                        else
                        {
                            UserRCommands( user, message, separator[1]);
                        }
                        break;
                        //how to use: roll.number
                    case "roll":
                        if(user.Equals("daniellinye") || user.Equals(channelname))
                        {
                            Console.WriteLine(Math.Round(Int32.Parse(separator[1]) * r.NextDouble()));
                        }
                        break;
                    
                }

            }
            catch(Exception)
            {
                BotFunctions.Say(user + ": invalid shout, try again.", stream);
            }

        }

        public void UserRCommands(string user, string message, string command)
        {
            if (command.Equals("add"))
            {

            }
            switch(command)
            {
                case "add":
                    foreach (Message msg in rafflelist)
                    {
                        if (msg.IsUser(user))
                        {
                            //do nothing if the user's already there
                            Console.WriteLine("User already in list");
                            break;
                        }
                    }
                    //if user's not in list add
                    rafflelist.Add(new Message(user, message));
                    Console.WriteLine("Added user " + user + " to the raffle.");
                    break;
                
            }
        }

        public void AdminRCommands(string command, DateTime time)
        {
            //TODO fix bug that 'clear' doesnt work
            Console.WriteLine(command);
            switch(command)
            {
                case "start":
                    rafflelist.Clear();
                    raffle = true;
                    break;
                case "show":
                    Console.WriteLine(rafflelist.ToString());
                    break;
                case "clear":
                    ClearList();
                    Console.WriteLine("Cleared list");
                    break;
                case "raffle":
                    Console.WriteLine(RandomUser());
                    break;
                case "stop":
                    Writefunctions wf = new Writefunctions(@"F:\stream", "raffle");
                    raffle = false;
                    wf.Write(rafflelist.ToString());
                    break;
                case "timed":
                    if(raffle == false)
                    {
                        time = DateTime.Now;
                        raffle = true;
                    }
                    break;
                default:
                    Console.WriteLine("Invalid shout, Admin.");
                    break;
            }
        }

        public void ClearList()
        {
            rafflelist = new List<Message>();
        }

        public Message RandomUser()
        {
            return rafflelist[(int)(r.NextDouble() * rafflelist.Count)];
        }
    }

    public class Message
    {
        string user, message;
        public Message(string user, string message)
        {
            this.user = user;
            this.message = message;

        }

        public string ReturnMessage()
        {
            return user + ':' + message;
        }

        public bool IsUser(string user)
        {
            if(this.user == user)
            {
                return true;
            }
            return false;
        }
    }

}
