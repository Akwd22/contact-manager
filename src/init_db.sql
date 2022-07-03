PRAGMA foreign_keys = ON;

DROP TABLE IF EXISTS General;
CREATE TABLE IF NOT EXISTS General (
  attribut            TEXT PRIMARY KEY NOT NULL,
  valeur              TEXT
);

DROP TABLE IF EXISTS Contact;
CREATE TABLE IF NOT EXISTS Contact (
  id                  INTEGER PRIMARY KEY,
  nom                 TEXT NOT NULL CHECK (nom <> ""),
  prenom              TEXT NOT NULL CHECK (prenom <> ""),
  entreprise          TEXT,
  email               TEXT,
  tel                 TEXT,
  photo               TEXT,
  date_modification   TEXT,
  date_creation       TEXT NOT NULL DEFAULT (DATE('now'))
);

DROP TABLE IF EXISTS Interaction;
CREATE TABLE IF NOT EXISTS Interaction (
  id                  INTEGER PRIMARY KEY,
  contenu             TEXT NOT NULL CHECK (contenu <> ""),
  date_creation       TEXT NOT NULL DEFAULT (DATE('now')),
  id_contact          INTEGER NOT NULL,

  FOREIGN KEY (id_contact) REFERENCES Contact(id)
    ON DELETE CASCADE
);

DROP TABLE IF EXISTS Todo;
CREATE TABLE IF NOT EXISTS Todo (
  id                  INTEGER PRIMARY KEY,
  resume              TEXT NOT NULL CHECK (resume <> ""),
  date_realisation    TEXT NOT NULL DEFAULT (DATE('now')),
  id_interaction      INTEGER NOT NULL,
  
  FOREIGN KEY (id_interaction) REFERENCES Interaction(id)
    ON DELETE CASCADE
);

INSERT INTO General VALUES
  ('dateSuppression', NULL);

INSERT INTO Contact(id, nom, prenom) VALUES
  (1, 'Dupont', 'Jean'),
  (2, 'Durand', 'Lucas');

INSERT INTO Interaction(id, contenu, id_contact) VALUES
  (1, 'Descriptif interaction 1\n@todo Faire les courses', 1),
  (2, 'Descriptif interaction 2', 2);

INSERT INTO Todo(id, resume, id_interaction) VALUES
  (1, 'Faire les courses', 1);