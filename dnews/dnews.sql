
DROP TABLE newsgroups;
CREATE TABLE newsgroups (
  id int unsigned PRIMARY KEY,
  name varchar(255)
);

CREATE TABLE newsheader (
  id int unsigned PRIMARY KEY,
  gid int unsigned,
  header text
);

CREATE TABLE news (
  id int unsigned PRIMARY KEY,
  body mediumtext
);