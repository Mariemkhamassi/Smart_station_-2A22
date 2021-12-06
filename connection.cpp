#include "connection.h"

Connection::Connection(){}

bool Connection::createconnection()
{
db = QSqlDatabase::addDatabase("QODBC");
bool test=false;
db.setDatabaseName("source_projet2A");//inserer le nom de la source de donnée ODBC
db.setUserName("Skira");//inserer le nom de l'utilisateur
db.setPassword("esprit18");//inserer le mot de passe de cet utilisateur
if(db.open()) test=true;

return test;
}

void Connection::closeConnection(){db.close();}
