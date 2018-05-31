using Gtk;
using System;
using System.Net.Sockets;
using System.Threading;
using System.Threading.Tasks;
using gui;
using System.Collections.Generic;

public partial class MainWindow : Gtk.Window
{
    private TcpClient client;
    private string username, password;
    private int id;
    private NetFunctions nf;

    static void Receive()
    {
        
    }

    public static string passingtext;

    public MainWindow(TcpClient client, string username, string password, int id) : base(Gtk.WindowType.Toplevel)
    {
        this.client = client;
        this.username = username;
        this.password = password;
        this.id = id;
        nf = new NetFunctions();


        Build();
        List<Label> labels = new List<Label>();

        labels.Add(label1);
        labels.Add(label2);
        labels.Add(label3);
        labels.Add(label4);
        labels.Add(label5);
        labels.Add(label6);
        labels.Add(label7);
        labels.Add(label8);
        labels.Add(label9);
        labels.Add(label10);
        labels.Add(label11);
        labels.Add(label12);
        labels.Add(label13);
        labels.Add(label14);
        labels.Add(label15);
        labels.Add(label16);
        labels.Add(label17);

        List<Button> buttons = new List<Button>();

        buttons.Add(button1);
        buttons.Add(button2);
        buttons.Add(button3);
        buttons.Add(button4);
        buttons.Add(button5);
        buttons.Add(button6);
        buttons.Add(button7);
        buttons.Add(button8);
        buttons.Add(button9);
        buttons.Add(button10);
    }

    protected void OnDeleteEvent(object sender, DeleteEventArgs a)
    {
        Application.Quit();
        a.RetVal = true;
    }

    protected async Task ListenerAsync()
    {
        NetworkStream stream = client.GetStream();
        string input = await Task.Run(()=> nf.Read(stream));

        if (input != String.Empty)
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
            label17.Text = input;
        }


    }

    protected async void Sender(string input)
    {
        NetworkStream stream = client.GetStream();
        nf.Message(stream, username, "Piet", input);
    }

    protected void sendmessages(object sender, EventArgs e)
    {
        entry1.Text = "";


        label17.Text = "yy";
        //thread sender

        

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


