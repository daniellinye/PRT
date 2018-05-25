using System;
using Gtk;
using System.IO;
using System.Net;
using System.Net.Sockets;

namespace gui
{
    public partial class Window : Gtk.Window
    {
        public Window() :
                base(Gtk.WindowType.Toplevel)
        {
            this.Build();
        }

        protected void Klick_login(object sender, EventArgs e)
        {
            //make username and password
            string username = String.Concat(".", username1.Text);
            string password = String.Concat(username, Password.Text);

            //standard values
            const Int32 port = 8080;
            const string ip = "127.0.0.1";

            //new clients
            TcpClient client = new TcpClient(ip, port);

            //new stream
            NetworkStream stream = client.GetStream();

            //pingpong server
            Console.WriteLine("Pinging Server");
            StreamWrite("Ping", stream);
            Console.WriteLine(Read(stream));

            //send actual command
            String message = SendCommand(stream, "Login", password);

            //read returning message


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

            client.Close();
        }

        //ALWAYS USE THIS COMMAND IN ORDER TO PREVENT DEADLOCK
        //except pingpong, pingpong is always fine
        public string SendCommand(NetworkStream stream, string commandtype, string args)
        {
            string total = String.Concat(commandtype, ":");
            total = String.Concat(commandtype, args);
            StreamWrite(total, stream);
            return Read(stream);
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

        public String StreamWrite(String input, NetworkStream stream)
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
