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
    public partial class RegisterWindow : Form
    {
        public RegisterWindow()
        {
            InitializeComponent();
        }

        private void BackToLogin_Click(object sender, EventArgs e)
        {

        }

        private void UserRegister_TextChanged(object sender, EventArgs e)
        {
            Statistics.username = UserRegister.Text;
        }

        private void PasswordRegister_TextChanged(object sender, EventArgs e)
        {
            Statistics.password = PasswordRegister.Text;
        }

        private void RegisterConfirm_Click(object sender, EventArgs e)
        {
            Statistics.nf.Register(Statistics.username, Statistics.password);
            Statistics.nf.SendCommands();
        }

        private void Back_Click(object sender, EventArgs e)
        {
            this.Hide();
            Form backtologin = new LoginWindow();
            backtologin.Show();
        }
    }
}
