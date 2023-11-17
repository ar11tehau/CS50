SELECT title from movies
INNER JOIN stars ON stars.movie_id = movies.id
INNER JOIN people ON stars.person_id = people.id
WHERE title IN (SELECT title FROM movies
INNER JOIN stars ON stars.movie_id = movies.id
INNER JOIN people ON stars.person_id = people.id
WHERE people.name="Helena Bonham Carter") AND people.name="Johnny Depp"
ORDER BY name;