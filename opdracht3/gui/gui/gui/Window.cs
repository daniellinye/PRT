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

            string username = String.Concat(".", username1.Text);
            string password = String.Concat(username, Password.Text);

            Int32 port = 8080;
            TcpClient client = new TcpClient("127.0.0.1", port);

            NetworkStream stream = client.GetStream();

            Console.WriteLine("Pinging Server");
            StreamWrite("Ping", stream);
            Read(stream);

            SendCommand(stream, "Login", password);

            String message = Read(stream);

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
        }

        public void SendCommand(NetworkStream stream, string commandtype, string args)
        {
            string total = String.Concat(commandtype, ":");
            total = String.Concat(commandtype, args);
            StreamWrite(total, stream);
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
