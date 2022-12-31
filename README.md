# Qyint-Community / gtk-chat-app
- - -

# Installing and Updating
### Installing:
`git clone https://github.com/Qyint-Community/gtk-chat-app` *download*
`cd gtk-test-app && chmod +x ./compile.sh` *make executable*
`./compile.sh` *compile*
`./client` *run application*

# Usage
### Login
After launching the Client, you will be greeted with a Login Window.
There, you can enter a username and a password.
This Information will be stored in `name.txt` and `pswd.txt`.
Currently, the Password is useless.
The Name will be sent with your Messages.
This Information will not be matched with a Database.
There is no way to stay logged in.
### Chat Client
After logging in, you will see the main Chat Client.
There, you can see the main Chat Window. It reads the Text from `server.txt`, which allows for easy server-side Scripts.
*Note: If server.txt does not exist, the Client will crash. Simply `touch server.txt` to fix this Issue.*
You can send a Message with the Format `[name] » [message]` by entering a Message into the Input Field and clicking the Send-Button.
You will not be able to see new Messages, unless you click the Refresh-Button or send a message.
The "Switch Servers" Button does not do anything at the Moment, but it should be easy to make it replace `server.txt` with a different Server.
There is also an Exit-Button.
** **
It shouldnt be too hard to expand on the Backend and build a working Chat App - except I wont.
I just created this for fun.

# Licensing
This Application is published under the QYINT-LICENSE.
