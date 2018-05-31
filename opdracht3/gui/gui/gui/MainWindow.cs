using System.Text;
using System.Collections.Generic;
using System;
using Gtk;
using System.IO;
using System.Threading;


public partial class MainWindow : Gtk.Window
{
    Thread hey = new Thread(Receive);

    static void Receive()
    {
        
    }

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
        List<Label> labels = new List<Label>
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

        button1.Label = hoi.ToString(); //ask for *th user online
        hoi++;
        button2.Label = hoi.ToString(); //ask for *th +1 user online
        hoi++;
        button3.Label = hoi.ToString(); //ask for *th +2 user online
        hoi++;
        button4.Label = hoi.ToString(); //ask for *th +3 user online
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

    protected void user1(object sender, EventArgs e) //establish connection user on place 1
    {
    }

    protected void user2(object sender, EventArgs e) //establish connection user on place 2
    {
    }

    protected void user3(object sender, EventArgs e) //establish connection user on place 3
    {
    }

    protected void user4(object sender, EventArgs e) //establish connection user on place 4
    {
    }

    protected void user5(object sender, EventArgs e) //establish connection user on place 5
    {
    }

    protected void user6(object sender, EventArgs e) //establish connection user on place 6
    {
    }

    protected void user7(object sender, EventArgs e) //establish connection user on place 7
	{
	}
   
    protected void user8(object sender, EventArgs e) //establish connection user on place 8
    {
    }
  
    protected void user9(object sender, EventArgs e) //establish connection user on place 9
    {
    }
 
    protected void user10(object sender, EventArgs e) //establish connection user on place 10
    {
    }


}


