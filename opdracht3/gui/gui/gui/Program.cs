using System;
using System.Net;
using System.Net.Sockets;
using Gtk;
using System.Text;

namespace gui
{
	class MainClass
	{
         
		public static void Main (string[] args)
		{
			Application.Init ();
            Window login = new Window();
            login.Show();


			Application.Run ();
		}
	}
}
