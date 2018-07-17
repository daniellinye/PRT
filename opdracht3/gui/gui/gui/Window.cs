using System;
using Gtk;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Collections;
using System.Collections.Generic;

namespace gui
{
    public partial class Window : Gtk.Window
    {
        string selecteduser = "Piet";
        public Window() :
                base(Gtk.WindowType.Toplevel)
        {
            this.Build();
        }



        protected void click(object sender, EventArgs e)
        {
            string message = "", username = "", password = "";
            NetFunctions nf = new NetFunctions();
            TcpClient client = new TcpClient();
            NetworkStream stream = null;
            try
            {
                //make username and password
                username = username1.Text;
                password = Password.Text;

                //standard values
                const Int32 port = 8081;
                const string ip = "127.0.0.1";

                //new clients
                client = new TcpClient(ip, port);

                //new stream
                stream = client.GetStream();



                //read returning message
                nf.Login(stream, username, password);
            }
            catch
            {
                message = "Could not connect to databse";
                username = "lol";
            }


            //give popup if the username wasn't empty
            if (username != String.Empty)
            {

                MessageDialog dlog = new MessageDialog
                    (
                        this, DialogFlags.Modal,
                        MessageType.Info,
                        ButtonsType.Ok,
                        message
                    );
                dlog.Run();
                dlog.Destroy();
            }
            //close client
            //TODO: replace this here when message is 
            //actually that someone has logged in
        //    if(nf.id != 0)
            {
                MainWindow win = new MainWindow(username, password, 0);
                Thread connect = new Thread(() => win.InitConnection());
                connect.Start();
                Thread listen = new Thread(() => win.ListenerAsync());
                
                //listen.Start();
                win.Show();
            }
        }

        protected void regristreren(object sender, EventArgs e) 
        {
            //TODO: tell server to make a new useraccount

            //make username and password
            string username = username1.Text;
            string password = Password.Text;

            // if error


            MessageDialog dlog = new MessageDialog
            (
                this, DialogFlags.Modal,
                MessageType.Info,
                ButtonsType.Ok,
                "try a different user combination/password"
            );
            dlog.Run();
            dlog.Destroy();

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




        //TODO: redo the entire parser such that it fits the parser from the server
        //TODO
        //TODO
        //TODO




        //sends a login command to the server
        //FORMAT; Login:"username"."password"
        //sends a login command to the server
        //FORMAT; Login:"username"."password"
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

            while(reading != "")
            {
                users.Add(reading);
            }

            return users;
        }

        public void AddCommand(string command, string[] args)
        {
            commands.Append(command);
            commands.Append(":");

            foreach(string arg in args)
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
