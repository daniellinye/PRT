using System;
using Gtk;
using System.IO;
namespace gui


{
    public partial class Window : Gtk.Window
    {
        public Window() :
                base(Gtk.WindowType.Toplevel)
        {
            this.Build();
        }

        protected void Klick_login(object sender, EventArgs e)
        {
            int intTemp = Convert.ToInt32(username1.Text);
            if (intTemp == 1)
            {
                
                MessageDialog dlog = new MessageDialog
                    (
                        this, DialogFlags.Modal,
                        MessageType.Info,
                        ButtonsType.Ok,
                        "YOU SHALL NOT PASS"
                    );
                dlog.Run();
                dlog.Destroy();
            }         
        }
    }
        
}
