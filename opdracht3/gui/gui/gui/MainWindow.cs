using System.Text;
using System;
using Gtk;
using System.IO;


public partial class MainWindow : Gtk.Window
{
    public static string passingtext;

    public MainWindow() : base(Gtk.WindowType.Toplevel)
    {
        Build();
    }

    protected void OnDeleteEvent(object sender, DeleteEventArgs a)
    {
        Application.Quit();
        a.RetVal = true;
    }
    protected void OnButton1Clicked(object sender, EventArgs ea)
    {
        MessageDialog dlog = new MessageDialog
            (
                this, DialogFlags.Modal,
                MessageType.Info,
                ButtonsType.Ok,
                "YOU SHALL NOT PASS"
            );
        dlog.Run();
        dlog.Destroy();
    }
    protected void OnButton2Clicked(object sender, EventArgs ea)
    {
        MessageDialog dlog = new MessageDialog
            (
                this, DialogFlags.Modal,
                MessageType.Info,
                ButtonsType.Ok,
                "YOU SHALL NOT PASS"
            );
        dlog.Run();
        dlog.Destroy();
    }

    protected void sendmessages(object sender, EventArgs e)
    {
        label1.Text = label2.Text;
        label2.Text = label3.Text;
        label3.Text = label4.Text;
        label4.Text = label5.Text;
        label5.Text = label6.Text;
        label6.Text = label7.Text;
        label7.Text = label8.Text;
        label8.Text = label9.Text;
        label9.Text = label10.Text;
        label10.Text = label11.Text;
        label11.Text = label12.Text;
        label12.Text = label13.Text;
        label13.Text = label14.Text;
        label14.Text = label15.Text;
        label15.Text = label16.Text;
        label16.Text = label17.Text;
        label17.Text = entry1.Text ;
        entry1.Text = "";

//        MessageDialog dlog = new MessageDialog
//            (
//                this, DialogFlags.Modal,
//                MessageType.Info,
//                ButtonsType.Ok,
//        "YOU SHALL NOT PASS"
//    );
//        dlog.Run();
//        dlog.Destroy();
    }

    protected void test(object o, KeyPressEventArgs args)
    {
    }
}


