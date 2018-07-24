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
        private static object sleep;

        public Chatwindow()
        {
            InitializeComponent();
        }

        public static void Updater()
        {
            Thread.Sleep(500);

            if(Statistics.recipient != null)
            {
                Statistics.nf.Update(Statistics.username, Statistics.recipient);
            }
            Statistics.nf.Online();
            Statistics.nf.SendCommands();

        }

        private void Chatwindow_Load(object sender, EventArgs e)
        {
            ThreadStart timers = new ThreadStart(Updater);
            Thread current = Thread.CurrentThread;
            Thread update = new Thread(timers);
            current.Start();
            update.Start();
        }

        private void button1_Click(object sender, EventArgs e)
        {

        }

        private void OnlineUsers_SelectedIndexChanged(object sender, EventArgs e)
        {
            OnlineUsers.DataSource = Statistics.onlineusers;
            Statistics.recipient = OnlineUsers.SelectedText;
        }

        private void MessageBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            MessageBox.DataSource = Statistics.usermessages;
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
    }
}
