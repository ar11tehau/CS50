SELECT people.name from people
INNER JOIN movies ON stars.movie_id = movies.id
INNER JOIN stars ON stars.person_id = people.id
WHERE title IN (SELECT title FROM movies
INNER JOIN stars ON stars.movie_id = movies.id
INNER JOIN people ON stars.person_id = people.id
WHERE people.name="Kevin Bacon" AND people.birth=1958) AND NOT people.name="Kevin Bacon"
ORDER BY name;