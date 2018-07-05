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
        /// <returns></returns>
        string ThreadConnections();

        /// <summary>
        /// Gives a connection request to server
        /// </summary>
        /// <returns>Returns a hash string for that connection</returns>
        string Connect();
        
        /// <summary>
        /// Gives a login request to server
        /// Parser: LOGIN#hashstring#username#password
        /// </summary>
        /// <returns></returns>
        string Login();

        /// <summary>
        /// Gives a message request to server
        /// Parser: MESSAGE#hashstring#username
        /// </summary>
        /// <returns></returns>
        string Message();

        /// <summary>
        /// Gives an update request to server
        /// Parser: UPDATE#username#hashstring
        /// </summary>
        /// <returns></returns>
        string Update();
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
        /// <param name="input"></param>
        /// <param name="username"></param>
        /// <returns>Returns wether this is true or not</returns>
        Boolean CheckHashInList(string input, string username);
    }
    
    interface ITcpFunctions
    {
        string TcpFunctions
        {
            get; set;
        }

        /// <summary>
        /// Simplify the new sessions and creation of listeners by using a function instead
        /// </summary>
        /// <param name="port"></param>
        /// <param name="ip"></param>
        /// <returns>Returns error codes if not succesfull</returns>
        string NewTcpListener(int port, string ip);

        /// <summary>
        /// Writes something to the current NetworkStream
        /// </summary>
        /// <param name="input"></param>
        /// <param name="stream"></param>
        void StreamWrite(string input, NetworkStream stream);
    }

    //***********************************************************************************************************************
    //classes
    //TODO: Implement API functions


    class Api : IApi
    {
        public string IApiInfo { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

        public string Connect()
        {
            throw new NotImplementedException();
        }

        public string Login()
        {
            throw new NotImplementedException();
        }

        public string Message()
        {
            throw new NotImplementedException();
        }

        public string ThreadConnections()
        {
            throw new NotImplementedException();
        }

        public string Update()
        {
            throw new NotImplementedException();
        }
    }

    class Hashes : IHashes
    {
        string IHashes.Hashes { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

        public bool CheckHashInList(string input, string username)
        {
            throw new NotImplementedException();
        }

        public string NewHash(string username)
        {
            throw new NotImplementedException();
        }
    }

    class TcpFunctions : ITcpFunctions
    {
        string ITcpFunctions.TcpFunctions { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

        enum TcpState { Read, Write };


        public string NewTcpListener(int port, string ip)
        {
            throw new NotImplementedException();
        }

        public void StreamWrite(string input, NetworkStream stream)
        {
            throw new NotImplementedException();
        }
    }
}
