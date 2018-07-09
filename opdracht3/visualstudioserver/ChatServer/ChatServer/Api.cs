using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;
using System.Globalization;
using System.IO;
using System.Runtime.InteropServices;
using System.Xml;
using System.Net.Sockets;
using System.Security.Cryptography;
using System.Net;
using System.Threading;

namespace ChatServer
{

    public interface IApi
    {
        //Imports info from an xml file
        string IApiInfo
        {
            get; set;
        }

        /// <summary>
        /// Manages threads in tcplisteners
        /// Such that multiple users are able to login
        /// </summary>
        /// <param name="ipadress"></param>
        /// <param name="port"></param>
        /// <returns></returns>
        string ThreadConnections(string ipadress, int port);

        /// <summary>
        /// Gives a login request to server
        /// Parser: LOGIN#username#password#hashstring
        /// </summary>
        /// <param name="username"></param>
        /// <param name="password"></param>
        /// <param name="hashcode"></param>
        /// <returns>Returns a hashstring such that sessions do not block each other</returns>
        string Login(string username, string password, string hashcode);

        /// <summary>
        /// Gives a logout request to the server
        /// Parser: LOGOUT#username#password#hashstring
        /// </summary>
        /// <param name="username"></param>
        /// <param name="password"></param>
        /// <param name="hashcode"></param>
        /// <returns></returns>
        string Logout(string username, string hashcode);

        /// <summary>
        /// Gives a message request to server
        /// Parser: MESSAGE#username#hashstring
        /// </summary>
        /// <param name="hashcode"></param>
        /// <param name="username"></param>
        /// <param name="recipient"></param>
        /// <returns></returns>
        string Message(string hashcode, string username, string recipient);

        /// <summary>
        /// Gives an update request to server
        /// Parser: UPDATE#username#hashstring
        /// </summary>
        /// <param name="username"></param>
        /// <param name="hashstring"></param>
        /// <returns></returns>
        string Update(string username, string hashstring);
    }

    interface IHashes
    {
        string Hashes
        {
            get; set;
        }

        /// <summary>
        /// Generates a new hashstring of random length (20 or longer)
        /// and numbers/letters such that sessions are safe
        /// </summary>
        /// <param name="username"></param>
        /// <returns></returns>
        string NewHash(string username);

        /// <summary>
        /// Checks wether the user is already present in the current list
        /// of connections
        /// </summary>
        /// <param name="hashcode"></param>
        /// <param name="username"></param>
        /// <returns>Returns wether this is true or not</returns>
        Boolean CheckHashInList(string hashcode, string username);
    }
    
    interface ISocketListener
    {

        /// <summary>
        /// Simplify the new sessions and creation of listeners by using a function instead
        /// </summary>
        /// <param name="port"></param>
        /// <param name="ip"></param>
        /// <returns>Returns error codes if not succesfull</returns>
        string NetSocketListener(int port, string ip);

        /// <summary>
        /// Helps with using the main signal,
        /// simplifies functions
        /// </summary>
        /// <param name="ar"></param>
        /// <returns></returns>
        void ListenerHelper(IAsyncResult ar);

        /// <summary>
        /// Helps during asynch streamreading
        /// </summary>
        /// <param name="ar"></param>
        void StreamHelper(IAsyncResult ar);

        /// <summary>
        /// Parses the string according to the commands
        /// given in the Api described above
        /// </summary>
        /// <param name="clientinput"></param>
        /// <returns></returns>
        int Parser(string clientinput);

        /// <summary>
        /// Writes something to the current NetworkStream
        /// </summary>
        /// <param name="input"></param>
        /// <param name="stream"></param>
        void StreamWrite(string input, Socket helper);

    }

    //***********************************************************************************************************************
    //classes
    //TODO: Implement API functions

    public class Reader
    {
        //is nested class such that Read is pretty much replaced
        //which is needed because we're using sockets
        public Socket socket = null;
        public const int buffersize = 1024;
        public byte[] buffer = new byte[buffersize];
        public StringBuilder sb = new StringBuilder();
    }

    class Api : IApi
    {
        public string IApiInfo { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }
        public Hashes hashcodes = new Hashes();
        protected string ipadress;
        protected int port;
        protected DatabaseFunctions df = new DatabaseFunctions();

        public Api(string ipadress, int port)
        {
            this.ipadress = ipadress;
            this.port = port;
        }

        public string Login(string username, string password, string hashcode)
        {
            bool exists = df.LogIn(username, password);
            if(exists)
            {
                return hashcodes.NewHash(username);
            }
            return "Login Unsuccessfull.";
        }

        public string Logout(string username, string hashcode)
        {
            bool exists = hashcodes.RemoveHash(username, hashcode);
            if(exists)
            {
                return "Logout successfull.";
            }
            return "ERROR 404: USER NOT FOUND IN LIST, RELOG TO SERVER";
        }

        public string Message(string hashcode, string username, string recipient)
        {
            throw new NotImplementedException();
        }

        public string ThreadConnections(string ipadress, int port)
        {
            throw new NotImplementedException();
        }

        public string Update(string username, string hashstring)
        {
            throw new NotImplementedException();
        }
    }

    class Hashes : IHashes
    {
        string IHashes.Hashes { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

        List<string[]> hashEntries = new List<string[]>();

        public bool CheckHashInList(string hashcode, string username)
        {
            foreach(string[] entries in hashEntries)
            {
                if(entries[0].Equals(username) && entries[1].Equals(hashcode))
                {
                    return true;
                }
            }
            return false;
        }

        public string NewHash(string username)
        {
            var bytes = new byte[255];
            using (var rand = new RNGCryptoServiceProvider())
            {
                rand.GetBytes(bytes);
            }
            string hash = BitConverter.ToString(bytes);
            //check if by miracle a hash of same characters exists
            foreach(string[] hashcodes in hashEntries)
            {
                if(hashcodes[1].Equals(hash))
                {
                    hash = NewHash(username);
                    return hash;
                }
            }
            hashEntries.Add(new string[2] { username, hash });
            return hash;
        }

        public bool RemoveHash(string username, string hashcode)
        {
            foreach (string[] entries in hashEntries)
            {
                if (entries[0] == username && entries[1] == hashcode)
                {
                    hashEntries.Remove(entries);
                    return true;
                }
            }
            return false;
        }
    }

    class SocketListener : ISocketListener
    {
        protected ManualResetEvent mre = new ManualResetEvent(false);

        public string NetSocketListener(int port, string ip)
        {
            try
            {
                //new network values
                IPAddress iaddress = IPAddress.Parse(ip);
                IPEndPoint endpoint = new IPEndPoint(iaddress, port);

                //net socket
                Socket listen = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "Starting");

                while (true)
                {
                    //reset to non signal state
                    mre.Reset();

                    //use asynchcallback to listen for connection asynchronously
                    listen.Bind(endpoint);
                    listen.Listen(100);
                    listen.BeginAccept(new AsyncCallback(ListenerHelper), listen);

                    //wait until done
                    mre.WaitOne();

                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                Console.WriteLine(DateTime.Now.ToString("[HH:mm:ss] ") + "Tried new socket, but crashed");
                Console.ReadLine();
            }
            return "";
        }

        public void ListenerHelper(IAsyncResult ar)
        {
            //Signal to continue main thread
            mre.Set();

            //Get sockets such that we can get a client
            Socket listen = (Socket)ar.AsyncState;
            Socket helper = listen.EndAccept(ar);

            Reader r = new Reader();
            r.socket = helper;

            helper.BeginReceive(r.buffer, 0, Reader.buffersize, 0, new AsyncCallback(StreamHelper), r);
        
        }

        public void StreamHelper(IAsyncResult ar)
        {
            string temp;
            Reader r = (Reader)ar.AsyncState;
            Socket helper = r.socket;

            int output = helper.EndReceive(ar);

            if(output > 0)
            {
                r.sb.Append(Encoding.ASCII.GetString(r.buffer, 0, output));


                temp = r.sb.ToString();
                if(temp.IndexOf("<EOF>") > -1)
                {
                    //if all content is read, proceed
                    Parser(temp);
                }
                else
                {
                    //otherwise continue to read in thread
                    helper.BeginReceive(r.buffer, 0, Reader.buffersize, 0, new AsyncCallback(StreamHelper), r);
                }
                
            }
        }

        public void StreamWrite(string input, Socket helper)
        {
            //convert the string data to bytes using ASCII
            byte[] byteData = Encoding.ASCII.GetBytes(input);

            helper.BeginSend(byteData, 0, byteData.Length, 0,
                new AsyncCallback(SendBack), helper);
        }

        private static void SendBack(IAsyncResult ar)
        {
            //when sends back to client, close the stream
            try
            {
                Socket helper = (Socket)ar.AsyncState;

                int bytesSent = helper.EndSend(ar);

                helper.Shutdown(SocketShutdown.Both);
                helper.Close();

            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }

        public int Parser(string clientinput)
        {
            //TODO: implement parser from api
            //TODO: return codes depending on succesfull or not
            //returning 1 == successfull
            throw new NotImplementedException();
        }
    }
}
