#ifndef LIGNE_H
#define LIGNE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QMessageBox>
#include <QDate>



class ligne
{

public:
    ligne(){}
    ligne(int,QString,QString,int,QDate);//constructeur par defaut

    QString getdepart(){return depart;}
    QString getarrive(){return arrive;}




    int getid_l(){return id_l;}
    int getkilometrage(){return kilometrage;}

    void setdepart(QString d){depart=d;}
    void setarrive(QString a){arrive=a;}
    void setid_l(int id_l){this->id_l=id_l;}
    void setkilometrage(int kilometrage){this->kilometrage=kilometrage;}
    void setdate_n(QDate date_n){this ->date_n=date_n;}

    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficherRech(QString,QString);
    QSqlQueryModel* afficherTri(QString);
bool supprimer(int id_l);
bool modifier(int,QString,QString,int);
bool recherche_mod(int);

private:
int id_l,kilometrage;
QString depart, arrive;
QDate date_n;
};
#endif // LIGNE_H




