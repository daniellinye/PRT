CREATE TABLE chatbox (chatid INTEGER, idfrom INTEGER, idto INTEGER, chatroom INTEGER,
            message CHAR(80) , PRIMARY KEY (chatid, chatroom),
            FOREIGN KEY (idfrom) REFERENCES users (id), FOREIGN KEY (idto) REFERENCES users (id));