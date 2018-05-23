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
            int intTemp = Convert.ToInt32(username1.Text);

            Int32 port = 8080;
            TcpClient client = new TcpClient("127.0.0.1", port);

            NetworkStream stream = client.GetStream();

            String message = Read(stream);

            if (intTemp == 1)
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


        
}
