using Gtk;
using System;
using System.Net.Sockets;
using System.Threading;
using System.Threading.Tasks;
using gui;
using System.Collections.Generic;
using System.Net.Sockets;

public partial class MainWindow : Gtk.Window
{
    private TcpClient client;
    private NetworkStream stream;
    private string username, password;
    private int id;
    private NetFunctions nf;
    List<Button> buttons;
    List<Label> labels;

    static void Receive()
    {
        
    }

    public static string passingtext;

    public MainWindow(string username, string password, int id) : base(Gtk.WindowType.Toplevel)
    {
        this.username = username;
        this.password = password;
        this.id = id;

        Build();
        labels = new List<Label>();

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

        buttons = new List<Button>();

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

        Thread t = new Thread(() => getUsers());
        t.Start();
    }

    public void InitConnection()
    {
        NetFunctions nf = new NetFunctions();
        this.client = new TcpClient();
        NetworkStream stream = null;
        string message;
        try
        {

            //standard values
            const Int32 port = 8080;
            const string ip = "127.0.0.1";

            //new clients
            client = new TcpClient(ip, port);

            stream = client.GetStream();

            //read returning message
            //TODO: make listen function
            message = nf.Login(stream, username, password);
        }
        catch
        {
            message = "Could not connect to databse";
            username = String.Empty;
        }
    }

    protected void OnDeleteEvent(object sender, DeleteEventArgs a)
    {
        Application.Quit();
        a.RetVal = true;
    }

    public async Task ListenerAsync()
    {
        while(true)
        {
            Thread.Sleep(200);
            //standard values
            const Int32 port = 8080;
            const string ip = "127.0.0.1";

            //new clients
            TcpClient client = new TcpClient(ip, port);

            nf = new NetFunctions();

            NetworkStream stream = client.GetStream();
            string input = nf.GetMessages(stream);

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



    }

    protected void Sender(string input)
    {
        NetFunctions nf = new NetFunctions();
        TcpClient client = new TcpClient();
        NetworkStream stream = null;
        string message;
        try
        {

            //standard values
            const Int32 port = 8080;
            const string ip = "127.0.0.1";

            //new clients
            client = new TcpClient(ip, port);

            stream = client.GetStream();

            //sendmessage
            nf.Message(stream, username, "Piet", input);
        }
        catch
        {
            message = "Could not connect to databse";
            username = String.Empty;
        }


    }

    protected void getUsers()
    {
        NetFunctions nf = new NetFunctions();
        while (true)
        {

            string message;
            try
            {

                //standard values
                const Int32 port = 8080;
                const string ip = "127.0.0.1";

                //new clients
                TcpClient client = new TcpClient(ip, port);

                NetworkStream stream = client.GetStream();

                //sendmessage
                List<string> users = nf.GetUsers(stream);
                int i = 0;
                if(i < buttons.Count)
                    foreach(string user in users)
                    {
                        buttons[i].Label = user;
                        labels[i].Text = user;
                        i++;
                    }
            }
            catch(Exception e)
            {
                label1.Text = e.ToString();
                message = "Could not connect to databse";
                username = String.Empty;
            }
            Thread.Sleep(50);
        }
    }

    //is bound to texbox
    protected void sendmessages(object sender, EventArgs e)
    {

        label17.Text = entry1.Text;

        if(entry1.Text != "")
        {
            //thread sender
            Thread send = new Thread(()=> Sender(entry1.Text));
            send.Start();

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
            label17.Text = entry1.Text;
        }

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


