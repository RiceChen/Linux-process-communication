Compile sqlite3 source code

gcc database.c -o database -lsqlite3

Change from .db to .sql

sqlite3 <filename>.db ".dump" > <filename>.sql