SELECT name FROM people
INNER JOIN directors ON directors.person_id = people.id
INNER JOIN movies ON movies.id = directors.movie_id
INNER JOIN ratings on ratings.movie_id = directors.movie_id
WHERE ratings.rating>=9
GROUP BY name
ORDER BY ratings.rating;