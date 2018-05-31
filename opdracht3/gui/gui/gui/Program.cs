using System;
using Gtk;

namespace gui
{
	class MainClass
	{
         
		public static void Main (string[] args)
		{
			Application.Init ();
            Window login = new Window();
            login.Show();
            MainWindow win = new MainWindow();
            win.Show();

			Application.Run ();
		}
	}
}
