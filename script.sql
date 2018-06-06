CREATE TABLE IF NOT EXISTS USERS (
mac TEXT PRIMARY KEY,
name TEXT,
addDate DATE,
lastSync DATE,
device TEXT
);

CREATE TABLE IF NOT EXISTS APPS (
app TEXT PRIMARY KEY,
version TEXT,
addDate DATE,
comment TEXT
);

CREATE TABLE IF NOT EXISTS TAGS (
tag TEXT,
mac TEXT,
color TEXT,
addDate DATE,
comment TEXT,
PRIMARY KEY(tag, mac),
FOREIGN KEY(mac) REFERENCES USERS(mac)
);

CREATE TABLE IF NOT EXISTS TAGS_USERS (
tag TEXT,
mac TEXT,
PRIMARY KEY(tag, mac),
FOREIGN KEY(tag) REFERENCES TAGS(tag),
FOREIGN KEY(mac) REFERENCES USERS(mac)
);

CREATE TABLE IF NOT EXISTS TAGS_URLS (
url TEXT,
tag TEXT,
title TEXT,
comment TEXT,
mime TEXT,
addDate DATE,
PRIMARY KEY(url, tag),
FOREIGN KEY(tag) REFERENCES TAGS(tag)
);

CREATE TABLE IF NOT EXISTS APPS_USERS (
mac TEXT,
app TEXT,
addDate DATE,
PRIMARY KEY(mac, app),
FOREIGN KEY(mac) REFERENCES USERS(mac),
FOREIGN KEY(app) REFERENCES APPS(app)
);

CREATE TABLE IF NOT EXISTS ABSTRACT (
app TEXT,
llave TEXT,
grupo TEXT,
addDate DATE,
comment TEXT,
PRIMARY KEY(app, llave, grupo),
FOREIGN KEY(app) REFERENCES APPS(app)
);

CREATE TABLE IF NOT EXISTS TAGS_ABSTRACT (
app TEXT,
tag TEXT,
llave TEXT,
grupo TEXT,
comment TEXT,
addDate DATE,
PRIMARY KEY(app, tag, llave, grupo),
FOREIGN KEY(app) REFERENCES APPS(app),
FOREIGN KEY(llave) REFERENCES ABSTRACT(llave),
FOREIGN KEY(grupo) REFERENCES ABSTRACT(grupo),
FOREIGN KEY(tag) REFERENCES TAGS(tag)
);

