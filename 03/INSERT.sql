-- Заполнение таблицы Исполнители
INSERT INTO Artists (artist_id, name)
VALUES
    (1, 'Bob'),
    (2, 'Артист 2'),
    (3, 'Артист 3'),
    (4, 'Артист 4');

-- Заполнение таблицы Жанры
INSERT INTO Genres (genre_id, name)
VALUES
    (1, 'Жанр 1'),
    (2, 'Жанр 2'),
    (3, 'Жанр 3');

-- Заполнение таблицы Альбомы
INSERT INTO Albums (album_id, title, release_year)
VALUES
    (1, 'Альбом 1', 2018),
    (2, 'Альбом 2', 2019),
    (3, 'Альбом 3', 2020);

-- Заполнение таблицы Треки
INSERT INTO Tracks (track_id, title, duration, album_id)
VALUES
    (1, 'Трек_my', 240, 1),
    (2, 'Трек 2', 210, 1),
    (3, 'Трек 3', 300, 2),
    (4, 'Трек 4', 330, 2),
    (5, 'Трек 5', 260, 3),
    (6, 'Трек 6', 280, 3);

-- Заполнение таблицы Сборники
INSERT INTO Compilations (compilation_id, title, release_year)
VALUES
    (1, 'Сборник 1', 2018),
    (2, 'Сборник 2', 2019),
    (3, 'Сборник 3', 2020);

-- Заполнение таблицы Исполнители_Альбомы
INSERT INTO Artist_Albums (artist_id, album_id)
VALUES
    (1, 1),
    (2, 2),
    (3, 3),
    (4, 1);

-- Заполнение таблицы Сборники_Треки
INSERT INTO Compilation_Tracks (compilation_id, track_id)
VALUES
    (1, 1),
    (1, 2),
    (2, 3),
    (2, 4),
    (3, 5),
    (3, 6);

-- Заполнение таблицы Исполнители_Жанры
INSERT INTO Artist_Genres (artist_id, genre_id)
VALUES
    (1, 1),
    (2, 2),
    (3, 1),
    (4, 3);
