using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FormAppClient
{
    public partial class Chatwindow : Form
    {
        List<string> _users = new List<string>();
        List<string[]> _messages = new List<string[]>();
        public Chatwindow()
        {
            InitializeComponent();

            //give list of online users
            Statistics.nf.Online();
            Statistics.nf.SendCommands();

            Console.WriteLine("users:");
            foreach (string users in Statistics.onlineusers)
            {
                Console.WriteLine(users);
                _users.Add(users);
            }

            listBox1.DataSource = _users;
        }

        public void Updater()
        {
            try
            {
                //do this every second
                Thread.Sleep(1000);

                //prep and send commands to server
                if (Statistics.recipient != null)
                {
                    Statistics.nf.Update(Statistics.username, Statistics.recipient);
                }
                Statistics.nf.Online();
                Statistics.nf.SendCommands();

                //update messages
                foreach (string[] messages in Statistics.usermessages)
                {
                    _messages.Add(messages);
                }

                //update userlist
                foreach (string users in Statistics.onlineusers)
                {
                    _users.Add(users);
                }

                //update gui
                listBox1.DataSource = null;
                listBox1.DataSource = _users;
                MessageBox.DataSource = null;
                MessageBox.DataSource = _messages;



            }
            catch
            {
                Console.WriteLine("Updater Crashed");
            }
            Updater();
        }

        private void Chatwindow_Load(object sender, EventArgs e)
        {
            try
            {
                ThreadStart timers = new ThreadStart(Updater);
                Thread update = new Thread(timers);
                update.Start();
            }
            catch
            {
                Console.WriteLine("Multithread died");
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Statistics.nf.Logout(Statistics.username, Statistics.nf.GetHashCode());
            Statistics.nf.SendCommands();
            Form login = new LoginWindow();
            this.Hide();
            login.Show();
        }

        private void OnlineUsers_SelectedIndexChanged(object sender, EventArgs e)
        {
            Statistics.recipient = Statistics.onlineusers[OnlineUsers.SelectedIndex];
        }

        private void MessageBox_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void UserText_TextChanged(object sender, EventArgs e)
        {
            Statistics.message = UserText.Text;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Statistics.nf.Message(Statistics.username, Statistics.recipient, Statistics.message);
            Statistics.nf.Update(Statistics.username, Statistics.recipient);
            Statistics.nf.SendCommands();
            UserText.Text = "";
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            try
            {
                Statistics.recipient = _users[listBox1.SelectedIndex];
            }
            catch
            {
            }
        }
    }
}
