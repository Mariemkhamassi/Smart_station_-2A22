#ifndef BUS_H
#define BUS_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
class bus
{
public:
    bus();
    bus(int,QString,QString,int,float);//constructeur parametré
    bool ajouter();
    bool modifier(int);
    bool supprimer(int);
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficherRech(QString,QString);
    QSqlQueryModel* afficherTri(QString);
    int compterBus();
 private:
    int id;
    QString marque;
    QString datefct;
    int nbrplaces;
    float kilometrage;

};

#endif // BUS_H
