using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FormAppClient
{
    public partial class LoginWindow : Form
    {
        public LoginWindow()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Hide();
            Form registering = new RegisterWindow();
            registering.Show();

        }


        private void Login_Click_1(object sender, EventArgs e)
        {
            Statistics.nf.Login(Statistics.username, Statistics.password);
            Statistics.nf.SendCommands();
            Form chatting = new Chatwindow();
            if(Statistics.nf.IsLoggedin())
            {
                this.Hide();
                chatting.Show();
            }
        }

        private void UserLogin_TextChanged_1(object sender, EventArgs e)
        {
            Statistics.username = UserLogin.Text;
        }

        private void PasswordLogin_TextChanged_1(object sender, EventArgs e)
        {
            Statistics.password = PasswordLogin.Text;
        }
    }
}
