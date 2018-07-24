namespace FormAppClient
{
    partial class RegisterWindow
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
            this.UserRegister = new System.Windows.Forms.TextBox();
            this.PasswordRegister = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.RegisterConfirm = new System.Windows.Forms.Button();
            this.Back = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // UserRegister
            // 
            this.UserRegister.Location = new System.Drawing.Point(150, 90);
            this.UserRegister.Name = "UserRegister";
            this.UserRegister.Size = new System.Drawing.Size(160, 20);
            this.UserRegister.TabIndex = 0;
            this.UserRegister.TextChanged += new System.EventHandler(this.UserRegister_TextChanged);
            // 
            // PasswordRegister
            // 
            this.PasswordRegister.Location = new System.Drawing.Point(150, 151);
            this.PasswordRegister.Name = "PasswordRegister";
            this.PasswordRegister.Size = new System.Drawing.Size(160, 20);
            this.PasswordRegister.TabIndex = 1;
            this.PasswordRegister.TextChanged += new System.EventHandler(this.PasswordRegister_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(74, 93);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(58, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Username:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(74, 154);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(56, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Password:";
            // 
            // RegisterConfirm
            // 
            this.RegisterConfirm.Location = new System.Drawing.Point(150, 205);
            this.RegisterConfirm.Name = "RegisterConfirm";
            this.RegisterConfirm.Size = new System.Drawing.Size(75, 23);
            this.RegisterConfirm.TabIndex = 5;
            this.RegisterConfirm.Text = "Register";
            this.RegisterConfirm.UseVisualStyleBackColor = true;
            this.RegisterConfirm.Click += new System.EventHandler(this.RegisterConfirm_Click);
            // 
            // Back
            // 
            this.Back.Location = new System.Drawing.Point(231, 205);
            this.Back.Name = "Back";
            this.Back.Size = new System.Drawing.Size(75, 23);
            this.Back.TabIndex = 6;
            this.Back.Text = "Back";
            this.Back.UseVisualStyleBackColor = true;
            this.Back.Click += new System.EventHandler(this.Back_Click);
            // 
            // RegisterWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(439, 275);
            this.Controls.Add(this.Back);
            this.Controls.Add(this.RegisterConfirm);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.PasswordRegister);
            this.Controls.Add(this.UserRegister);
            this.Name = "RegisterWindow";
            this.Text = "RegisterWindow";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox UserRegister;
        private System.Windows.Forms.TextBox PasswordRegister;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button RegisterConfirm;
        private System.Windows.Forms.Button Back;
    }
}