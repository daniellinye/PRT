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

        /*
         explanation login and pingpong:
         if ping
         write pong
         if login
         add to userlist
         if logout
         remove from userlist
         if message
         add to messagelist
             */

        private bool newuser;

        static void Main(string[] args)
        {
            Program p = new Program();
            Console.WriteLine("did stuff");
            p.Startup();
        }

        public void Startup()
        {


            //TODO: 
            //TODO: System.Netsockets Exception
            //TODO: Only one usage of each socket address, move this to an another place
            //aka make new function to reset when is dead

            DatabaseFunctions df = new DatabaseFunctions();

            df.LogIn("Robert", "wachtwoord");

            int buddyId = 1;
            df.SendMessage(buddyId, "Hallo Piet");
            df.GetMessages(buddyId);

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
                Console.WriteLine("Starting");
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
                        Thread t = new Thread(() => ListenToNewUser(client, listen, cf, cf.GetMostRecent().ReturnId()));
                        t.Start();
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                Console.WriteLine("Tried new socket, but crashed");
            }
        }

        //handles loginrequests
        public void LoginRequest(TcpClient client, TcpListener listen)
        {
            //parseclass
            ParseFunctions pf = new ParseFunctions();
            try
            {
                string input = pf.Read(client.GetStream());
                Console.WriteLine(input);

                if (input != String.Empty)
                {
                    if (pf.Parser(input, client))
                    {
                        newuser = true;
                        Console.WriteLine("User Logged in");
                        return;
                    }
                    else
                    {
                        pf.StreamWrite("Invalid login", client.GetStream());
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                Console.WriteLine("Loginrequest problems");
            }
            finally
            {
                client.Close();
                listen.Stop();
                Looper();
            }
        }

        //multithread to listen to the current users
        public void ListenToNewUser(TcpClient client, TcpListener listen, ConnectionFunctions cf, int id)
        {
            //parseclass
            ParseFunctions pf = new ParseFunctions();
            try
            {
                while (true)
                {
                    string input = pf.Read(client.GetStream());
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
                Console.WriteLine(e);
                Console.WriteLine("User {0} was forcibly logged out.", cf.GetName(id).ReturnName());
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
