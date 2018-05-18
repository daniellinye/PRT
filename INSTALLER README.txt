RELATED: How Do I Know if I’m Running 32-bit or 64-bit Windows?

This feature doesn’t work on the 32-bit version of Windows 10, so ensure you’re using the 64-bit version of Windows. It’s time to switch to the 64-bit version of Windows 10 if you’re still using the 32-bit version, anyway.

Assuming you have 64-bit Windows, to get started, head to Control Panel > Programs > Turn Windows Features On Or Off. Enable the “Windows Subsystem for Linux” option in the list, and then click the “OK” button.

Click “Restart now” when you’re prompted to restart your computer. The feature won’t work until you reboot.

To start bash, sipmply use the windows key and then type bash
to start the program.


Graphical Applications
In order to run Linux GUI applications on Bash On Ubuntu on Windows, you must:

Install a X server for Windows
Configure bash to tell GUIs to use the local X server
Install VcXsrv
In order to run graphical Linux applications, you’ll need an X server.

VcXsrv is the only fully open source and up-do-date native X server for windows.

Download and run the latest installer
Locate the VcXsrv shortcut in the Start Menu
Right click on it
Select More>Open file location
Copy the VcXsrv shortcut file
Paste the shortcut in %appdata%\Microsoft\Windows\Start Menu\Programs\Startup
Launch VcXsrv for the first time