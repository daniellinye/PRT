using System;
using Gtk;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace gui
{
    public partial class Window : Gtk.Window
    {
        public Window() :
                base(Gtk.WindowType.Toplevel)
        {
            this.Build();
        }



        protected void click(object sender, EventArgs e)
        {
            //make username and password
            string username = username1.Text;
            string password = Password.Text;

            //standard values
            const Int32 port = 8080;
            const string ip = "127.0.0.1";

            //new clients
            TcpClient client = new TcpClient(ip, port);

            //new stream
            NetworkStream stream = client.GetStream();

            NetFunctions nf = new NetFunctions();

            //read returning message
            string message = nf.Login(stream, username, password);



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
            if(nf.id != 0)
            {
                MainWindow win = new MainWindow(client, username, password, 0);
                Thread listen = new Thread(() => win.ListenerAsync());
                win.Show();
            }
        }
    }



    public class NetFunctions
    {
        //To be setuped when pinging server
        public int id;

        public NetFunctions()
        {
        
        }

        //sends a login command to the server
        //FORMAT; Login:"username"."password"
        //sends a login command to the server
        //FORMAT; Login:"username"."password"
        public string Login(NetworkStream stream, string username, string password)
        {
            try
            {
                StringBuilder sb = new StringBuilder();
                sb.Append(username);
                sb.Append(".");
                sb.Append(password);

                //send actual command
                string total = SendCommand(stream, "Login", sb.ToString());

                string[] idmessage = total.Split(':');
                id = Int32.Parse(idmessage[1]);
                return idmessage[0];
            }
            catch (Exception e)
            {   
                return e.ToString();
            }

        }

        //sends a message command to the server
        //FORMAT; Message:"user","recipient"."message"
        public string Message(NetworkStream stream, string username, string recipient, string message)
        {
            StringBuilder sb = new StringBuilder();
            //TODO: insert id as parameter when using the client
            sb.Append("Message");
            sb.Append(":");
            sb.Append(username);
            sb.Append(",");
            sb.Append(recipient);
            sb.Append(".");
            sb.Append(message);

            //send actual command
            return StreamWrite(sb.ToString(), stream);
        }

        //ALWAYS USE THIS COMMAND IN ORDER TO PREVENT DEADLOCK
        //except pingpong, pingpong is always fine
        public string SendCommand(NetworkStream stream, string commandtype, string args)
        {
            StringBuilder sb = new StringBuilder();
            sb.Append(commandtype);
            sb.Append(":");
            sb.Append(args);
            StreamWrite(sb.ToString(), stream);
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
