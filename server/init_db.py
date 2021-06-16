import sqlite3

connection = sqlite3.connect('database.db')


with open('schema.sql') as f:
    connection.executescript(f.read())

cur = connection.cursor()

# Eventueel execute statement toevoegen E.G.
# cur.execute("INSERT INTO calibration (table_height) VALUES (?)",
#             (165)
#             )


connection.commit()
connection.close()