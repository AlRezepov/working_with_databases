-- Название и продолжительность самого длительного трека:
SELECT title, duration
FROM Tracks
ORDER BY duration DESC
LIMIT 1;

-- Название треков, продолжительность которых не менее 3,5 минут:
SELECT title
FROM Tracks
WHERE duration >= 210;

-- Названия сборников, вышедших в период с 2018 по 2020 годы включительно:
SELECT title
FROM Compilations
WHERE release_year BETWEEN 2018 AND 2020;

-- Исполнители, чьё имя состоит из одного слова:
SELECT name
FROM Artists
WHERE name NOT LIKE '% %';

-- Название треков, которые содержат слова «мой» или «my»:
SELECT title
FROM Tracks
WHERE title LIKE '%мой%' OR title LIKE '%my%';

-- Количество исполнителей в каждом жанре:
SELECT g.name AS genre, COUNT(ag.artist_id) AS artist_count
FROM Genres g
LEFT JOIN Artist_Genres ag ON g.genre_id = ag.genre_id
GROUP BY g.name;

-- Количество треков, вошедших в альбомы 2019–2020 годов:
SELECT COUNT(*) AS track_count
FROM Tracks t
INNER JOIN Albums a ON t.album_id = a.album_id
WHERE a.release_year BETWEEN 2019 AND 2020;

-- Средняя продолжительность треков по каждому альбому:
SELECT a.title AS album, AVG(t.duration) AS avg_duration
FROM Albums a
INNER JOIN Tracks t ON a.album_id = t.album_id
GROUP BY a.title;

--Все исполнители, которые не выпустили альбомы в 2020 году:
SELECT a.name AS artist
FROM Artists a
LEFT JOIN Artist_Albums aa ON a.artist_id = aa.artist_id
LEFT JOIN Albums al ON aa.album_id = al.album_id
WHERE al.release_year IS NULL OR al.release_year != 2020;

-- Названия сборников, в которых присутствует конкретный исполнитель:
SELECT c.title AS compilation
FROM Compilations c
INNER JOIN Compilation_Tracks ct ON c.compilation_id = ct.compilation_id
INNER JOIN Tracks t ON ct.track_id = t.track_id
INNER JOIN Albums a ON t.album_id = a.album_id
INNER JOIN Artist_Albums aa ON a.album_id = aa.album_id
INNER JOIN Artists ar ON aa.artist_id = ar.artist_id
WHERE ar.name = 'Bob';