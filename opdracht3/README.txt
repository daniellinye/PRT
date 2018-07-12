Explanation backend API:
Commands are parsed in the following way:
<COMMAND>#<ARGS1>#<ARGS2>#<ARGS3>|
<COMMAND>#<ARGS1>#<ARGS2>#<ARGS3>|
<COMMAND>#<ARGS1>#<ARGS2>#<ARGS3>|
ect.
<EOF>

The server will send responses back in a similar fashion:
<COMMANDRESPONSEARG>:<ARGS>|
<COMMANDRESPONSEARG>:<ARGS>|
<COMMANDRESPONSEARG>:<ARGS>|
ect.
<EOF>

ARGS are all spaced with a '#' COMMANDS are spaced with a '|'
Following command requests with the descriptions are as follows:
------------------------
LOGIN
Parser: LOGIN#username#password
<returns> a hashstring. 
you'll need this in order to use other commands.
So make sure you save this somewhere in your program
------------------------
LOGOUT
Parser: LOGIN#username#hashcode
<returns> a responsecode wether is was successfull or not.
To secure a hashcode once again when a user logs out.
Must be called when the client is closed.
------------------------
MESSAGE
Parser: LOGIN#username#recipient#hashcode
<returns> a responsecode wether is was successfull or not.
------------------------
UPDATE
Parser: LOGIN#username#recipient#hashcode
<returns> a list with the messages spaced like: 
message:user|message:user|message:user
Used in order to either update the current chat or move to another chat.