#ifndef LIGNE_H
#define LIGNE_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QMessageBox>

class station
{

public:
    station(){}
    station(int,QString,int);


    int getID(){return id_s;}
    QString getloc(){return loc;}
    int getbus(){return nb_b;}


    void setID(int id_s){this->id_s=id_s;}
    void setloc(QString loc){this->loc=loc;}
    void setbus(int nb_b){this->nb_b=nb_b;}

bool ajouter();
QSqlQueryModel* afficher();
bool supprimer(int);
bool modifier(int,QString,int);
QSqlQueryModel* afficherRech(QString,QString);
QSqlQueryModel* afficherTri(QString);
int compter_s();

private:
int id_s;
QString loc;
int nb_b;
};
#endif // STATION_H




