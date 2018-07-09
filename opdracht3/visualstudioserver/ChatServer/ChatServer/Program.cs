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

        private bool newuser;

        static void Main(string[] args)
        {
            SocketListener sl = new SocketListener();
            sl.NetSocketListener(8081, "127.0.0.1");
            Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "Initialized TcpListener");
        }

        public void Startup()
        {

            Thread looper = new Thread(() => Looper());
            looper.Start();
        }

        public void Looper()
        {
            try
            {
                newuser = false;
                const int port = 8080;
                const string ip = "127.0.0.1";

                //start listening at 
                //port 8080

                ConnectionFunctions cf = new ConnectionFunctions();
                IPAddress iaddress = IPAddress.Parse(ip);
                TcpListener listen = new TcpListener(iaddress, port);
                Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "Starting");
                listen.Start();

                //connect client
                TcpClient client = listen.AcceptTcpClient();

                //fetch data
                NetworkStream stream = client.GetStream();
                while (true)
                {
                    LoginRequest(client, listen);

                    if (newuser)
                    {
                        newuser = false;
                        Thread restart = new Thread(new ThreadStart(Startup));
                        restart.Start();
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "Tried new socket, but crashed");
                Console.ReadLine();
            }
        }

        //handles loginrequests
        public void LoginRequest(TcpClient client, TcpListener listen)
        {

            try
            {
                string input = pf.Read(client.GetStream());
                Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "input:" + input);

                if (input != String.Empty)
                {
                    if (pf.Parser(input, client))
                    {
                        newuser = true;
                        Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "User Logged in");
                        return;
                    }
                    else
                    {
                        pf.StreamWrite(DateTime.Now.ToString("[HH:mm:ss] ") + "Invalid login", client.GetStream());
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("\n" + e + "\n");
                Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "Loginrequest problems");
            }
            finally
            {
                client.Close();
                listen.Stop();
                Looper();
            }
        }

        //multithread to listen to the current users
        public async void ListenToNewUser(TcpClient client, TcpListener listen, ConnectionFunctions cf, int id)
        {
            //parseclass
            ParseFunctions pf = new ParseFunctions();
            try
            {
                while (true)
                {
                    string input = await Task.Run(() => pf.Read(client.GetStream()));
                    Console.WriteLine(input);

                    if (input != String.Empty)
                    {
                        pf.Parser(input, client);
                    }
                    else
                    {
                        //logout user
                        cf.LogoutUser(cf.GetName(id).ReturnName(), id);
                    }

                }
            }
            catch (Exception e)
            {
                Console.WriteLine("\n" + e + "\n");
                Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "User {0} was forcibly logged out.", cf.GetName(id).ReturnName());
            }
            finally
            {
                //logout current user
                cf.LogoutUser(cf.GetName(id).ReturnName(), id);
            }

        }


        public static void Say(String input, NetworkStream stream)
        {
            string annstring = input;
            Byte[] announce = System.Text.Encoding.ASCII.GetBytes(annstring);
            stream.Write(announce, 0, announce.Length);
        }

    } // class Program
}
