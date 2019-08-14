#!/usr/bin/python
# -*- coding: UTF-8 -*-
# Importa o modulo de conexao com o mysql
import MySQLdb

# Gera a string de conexao ex.: seu host, seu usuario, sua senha e seu db
db = MySQLdb.connect(host="127.0.0.1", user="root", passwd="", db="teste")
# Posiciona o cursor
cursor = db.cursor()
# Executa a consulta na tabela selecionada
cursor.execute("SELECT * FROM teste.presenca")
# Conta o numero de linhas na tabela
numrows = int(cursor.rowcount)
# Obtendo resultados
print ("--------------------------------------------------")
print ("| ID Numero_Tag Nome                            | ")
print ("--------------------------------------------------")
# Laço for para retornar os valores, ex.: row[0] primeira coluna, row[1] segunda coluna, row[2] terceira coluna, etc.
for row in cursor.fetchall():
   print (row[0])
   print(row[1])
   print(row[2])
