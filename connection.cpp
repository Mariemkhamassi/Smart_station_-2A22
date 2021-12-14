#include "connection.h"

Connection::Connection(){}

bool Connection::createconnection()
{
db = QSqlDatabase::addDatabase("QODBC");
bool test=false;
db.setDatabaseName("projet_oracle");//inserer le nom de la source de donnée ODBC
db.setUserName("motazsammoud");//inserer le nom de l'utilisateur
db.setPassword("motaz");//inserer le mot de passe de cet utilisateur
if(db.open()) test=true;

return test;
}

void Connection::closeConnection(){db.close();}
