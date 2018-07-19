namespace FormAppClient
{
    partial class Chatwindow
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.OnlineUsers = new System.Windows.Forms.ComboBox();
            this.MessageBox = new System.Windows.Forms.ListBox();
            this.UserText = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // OnlineUsers
            // 
            this.OnlineUsers.FormattingEnabled = true;
            this.OnlineUsers.Location = new System.Drawing.Point(12, 12);
            this.OnlineUsers.Name = "OnlineUsers";
            this.OnlineUsers.Size = new System.Drawing.Size(239, 21);
            this.OnlineUsers.TabIndex = 0;
            // 
            // MessageBox
            // 
            this.MessageBox.FormattingEnabled = true;
            this.MessageBox.Location = new System.Drawing.Point(12, 52);
            this.MessageBox.Name = "MessageBox";
            this.MessageBox.Size = new System.Drawing.Size(409, 381);
            this.MessageBox.TabIndex = 1;
            // 
            // UserText
            // 
            this.UserText.Location = new System.Drawing.Point(12, 453);
            this.UserText.Name = "UserText";
            this.UserText.Size = new System.Drawing.Size(409, 20);
            this.UserText.TabIndex = 2;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(455, 12);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(152, 23);
            this.button1.TabIndex = 3;
            this.button1.Text = "LogOut";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(455, 450);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(152, 23);
            this.button2.TabIndex = 4;
            this.button2.Text = "Send";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // Chatwindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(619, 485);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.UserText);
            this.Controls.Add(this.MessageBox);
            this.Controls.Add(this.OnlineUsers);
            this.Name = "Chatwindow";
            this.Text = "Chatwindow";
            this.Load += new System.EventHandler(this.Chatwindow_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox OnlineUsers;
        private System.Windows.Forms.ListBox MessageBox;
        private System.Windows.Forms.TextBox UserText;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
    }
}