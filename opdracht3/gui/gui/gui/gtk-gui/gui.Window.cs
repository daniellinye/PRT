
// This file has been generated by the GUI designer. Do not modify.
namespace gui
{
	public partial class Window
	{
		private global::Gtk.Fixed fixed2;

		private global::Gtk.Entry username1;

		private global::Gtk.Entry Password;

		private global::Gtk.Label username;

		private global::Gtk.Label label3;

		private global::Gtk.Button button9;

		protected virtual void Build()
		{
			global::Stetic.Gui.Initialize(this);
			// Widget gui.Window
			this.Name = "gui.Window";
			this.Title = global::Mono.Unix.Catalog.GetString("Window");
			this.WindowPosition = ((global::Gtk.WindowPosition)(4));
			// Container child gui.Window.Gtk.Container+ContainerChild
			this.fixed2 = new global::Gtk.Fixed();
			this.fixed2.Name = "fixed2";
			this.fixed2.HasWindow = false;
			// Container child fixed2.Gtk.Fixed+FixedChild
			this.username1 = new global::Gtk.Entry();
			this.username1.CanFocus = true;
			this.username1.Name = "username1";
			this.username1.IsEditable = true;
			this.username1.InvisibleChar = '•';
			this.fixed2.Add(this.username1);
			global::Gtk.Fixed.FixedChild w1 = ((global::Gtk.Fixed.FixedChild)(this.fixed2[this.username1]));
			w1.X = 161;
			w1.Y = 78;
			// Container child fixed2.Gtk.Fixed+FixedChild
			this.Password = new global::Gtk.Entry();
			this.Password.CanFocus = true;
			this.Password.Name = "Password";
			this.Password.IsEditable = true;
			this.Password.InvisibleChar = '•';
			this.fixed2.Add(this.Password);
			global::Gtk.Fixed.FixedChild w2 = ((global::Gtk.Fixed.FixedChild)(this.fixed2[this.Password]));
			w2.X = 161;
			w2.Y = 126;
			// Container child fixed2.Gtk.Fixed+FixedChild
			this.username = new global::Gtk.Label();
			this.username.Name = "username";
			this.username.LabelProp = global::Mono.Unix.Catalog.GetString("Username");
			this.fixed2.Add(this.username);
			global::Gtk.Fixed.FixedChild w3 = ((global::Gtk.Fixed.FixedChild)(this.fixed2[this.username]));
			w3.X = 73;
			w3.Y = 81;
			// Container child fixed2.Gtk.Fixed+FixedChild
			this.label3 = new global::Gtk.Label();
			this.label3.Name = "label3";
			this.label3.LabelProp = global::Mono.Unix.Catalog.GetString("Password");
			this.fixed2.Add(this.label3);
			global::Gtk.Fixed.FixedChild w4 = ((global::Gtk.Fixed.FixedChild)(this.fixed2[this.label3]));
			w4.X = 75;
			w4.Y = 130;
			// Container child fixed2.Gtk.Fixed+FixedChild
			this.button9 = new global::Gtk.Button();
			this.button9.CanFocus = true;
			this.button9.Name = "button9";
			this.button9.UseUnderline = true;
			this.button9.Label = global::Mono.Unix.Catalog.GetString("Login");
			this.fixed2.Add(this.button9);
			global::Gtk.Fixed.FixedChild w5 = ((global::Gtk.Fixed.FixedChild)(this.fixed2[this.button9]));
			w5.X = 170;
			w5.Y = 193;
			this.Add(this.fixed2);
			if ((this.Child != null))
			{
				this.Child.ShowAll();
			}
			this.DefaultWidth = 400;
			this.DefaultHeight = 300;
			this.Show();
			this.button9.Clicked += new global::System.EventHandler(this.Klick_login);
		}
	}
}