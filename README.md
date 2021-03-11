# cheatsheet.nz Reference Sheet Generator

## Introduction

*cheatsheet.nz* is a reference sheet generator built with Flask and SQLite. It is designed for people who are after a quick way to access technical information and provides a uniform and dynamic template through which to display a variety of complex reference materials.

The layout is built on on CSS grid and flexbox and is fully responsive. It can be adapted for any topic which has a large number of elements.

*cheatsheet.nz* uses Flask and the inbuilt Jinja2 templating system. It connects to an SQLite database and runs a series of SQL queries to populate the menu, categories and reference items on the page. *cheatsheet.nz* also supports images and captions for topics which rely on visual aids.

## Changing the content

Data is stored in the following tables:

1. sheet
2. category
3. content

A custom sheet can be created so long as the original database structure and field names are followed.

## Future plans

*cheatsheet.nz* will be expanded to support multiple sheets, with a dropdown selector providing the user the ability to change reference sheets.
# jaywnz
# CS50x Problem Sets
Completed for Harvard's CS50x in 2020
1. scratch
2. hello
3. mario/more
4. credit
5. readbility
6. substitution
7. plurality
8. runoff
9. filter/more
10. recover
11. speller
12. sentimental/hello
13. sentimental/mario/more
14. sentimental/credit
15. sentimental/readability
16. dna
17. movies
18. houses
19. games/pong
20. games/mario
21. project
