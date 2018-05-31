CREATE TABLE users (
    Id       INT NOT NULL,
    username VARCHAR(10) NOT NULL,
    password VARCHAR(10) NOT NULL,
    online   BIT NULL,
    PRIMARY KEY (Id, username)
);

CREATE TABLE Messages (
    Mid       INT NOT NULL,
    description VARCHAR(255) NOT NULL,
    idfrom    INT NOT NULL,
    idto      INT NOT NULL,
    date      DATETIME,
    PRIMARY KEY (Mid ASC),
    FOREIGN KEY (idfrom) REFERENCES users(Id),
    FOREIGN KEY (idto) REFERENCES users(Id)
);