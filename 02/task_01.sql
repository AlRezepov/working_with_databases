-- Создание таблицы Исполнители
CREATE TABLE IF NOT EXISTS Artists (
    artist_id INT PRIMARY KEY,
    name VARCHAR(255)
);

-- Создание таблицы Жанры
CREATE TABLE IF NOT EXISTS Genres (
    genre_id INT PRIMARY KEY,
    name VARCHAR(255)
);

-- Создание таблицы Исполнители_Жанры
CREATE TABLE IF NOT EXISTS Artist_Genres (
    artist_id INT,
    genre_id INT,
    FOREIGN KEY (artist_id) REFERENCES Artists(artist_id),
    FOREIGN KEY (genre_id) REFERENCES Genres(genre_id)
);

-- Создание таблицы Альбомы
CREATE TABLE IF NOT EXISTS Albums (
    album_id INT PRIMARY KEY,
    title VARCHAR(255),
    release_year INT
);

-- Создание таблицы Исполнители_Альбомы
CREATE TABLE IF NOT EXISTS Artist_Albums (
    artist_id INT,
    album_id INT,
    FOREIGN KEY (artist_id) REFERENCES Artists(artist_id),
    FOREIGN KEY (album_id) REFERENCES Albums(album_id)
);

-- Создание таблицы Треки
CREATE TABLE IF NOT EXISTS Tracks (
    track_id INT PRIMARY KEY,
    title VARCHAR(255),
    duration INT,
    album_id INT,
    FOREIGN KEY (album_id) REFERENCES Albums(album_id)
);

-- Создание таблицы Сборники
CREATE TABLE IF NOT EXISTS Compilations (
    compilation_id INT PRIMARY KEY,
    title VARCHAR(255),
    release_year INT
);

-- Создание таблицы Сборники_Треки
CREATE TABLE IF NOT EXISTS Compilation_Tracks (
    compilation_id INT,
    track_id INT,
    FOREIGN KEY (compilation_id) REFERENCES Compilations(compilation_id),
    FOREIGN KEY (track_id) REFERENCES Tracks(track_id)
);


