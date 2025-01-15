// sql_client.h
#ifndef SQL_CLIENT_H
#define SQL_CLIENT_H

#include <mysql/mysql.h>  // Assurez-vous que mysql.h est inclus ici

// Déclaration des fonctions utilisées dans main.c
void init_connection(MYSQL **conn);
void close_connection(MYSQL *conn);
void execute_query(MYSQL *conn, const char *query);

#endif // SQL_CLIENT_H
