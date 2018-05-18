using System;
using Gtk;
using System.IO;


public partial class MainWindow: Gtk.Window
{
	public MainWindow () : base (Gtk.WindowType.Toplevel)
	{
		Build ();
	}

	protected void OnDeleteEvent (object sender, DeleteEventArgs a)
	{
		Application.Quit ();
		a.RetVal = true;
	}
    protected void OnButton1Clicked(object sender, EventArgs ea)
    {
        MessageDialog dlog = new MessageDialog
            (
                this, DialogFlags.Modal,
                MessageType.Info,
                ButtonsType.Ok,
                "Hello world :P"
            );
        dlog.Run();
        dlog.Destroy();
    }

}



