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

    protected void scroll(object o, ChangeValueArgs args)
    {
        int hoi = Convert.ToInt32(persoonbar.Value);

        button1.Label = hoi.ToString();
        hoi++;
        button2.Label = hoi.ToString();
        hoi++;
        button3.Label = hoi.ToString();
        hoi++;
        button4.Label = hoi.ToString();
        hoi++;
        button5.Label = hoi.ToString();
        hoi++;
        button6.Label = hoi.ToString();
        hoi++;
        button7.Label = hoi.ToString();
        hoi++;
        button8.Label = hoi.ToString();
        hoi++;
        button9.Label = hoi.ToString();
        hoi++;
        button10.Label = hoi.ToString();
    }

//    protected void Click herclie to add a new handler(object sender, EventArgs e)
//    {
//    }

    protected void user1(object sender, EventArgs e)
    {
    }

    protected void user3(object sender, EventArgs e)
    {
    }

    protected void user4(object sender, EventArgs e)
    {
    }

    protected void user5(object sender, EventArgs e)
    {
    }

    protected void user6(object sender, EventArgs e)
    {
    }

    protected void user7(object sender, EventArgs e)
	{
	}
   
    protected void user8(object sender, EventArgs e)
    {
    }
  
    protected void user9(object sender, EventArgs e)
    {
    }
 
    protected void user10(object sender, EventArgs e)
    {
    }
}


