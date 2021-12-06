#ifndef ABONNEMENT_H
#define ABONNEMENT_H

#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QMessageBox>
#include <QDate>
class abonnement
{

public:
    abonnement(){}
    abonnement(int,QDate,QDate);


    int getID(){return id;}


    void setdate_1(QDate date_1){this ->date_1=date_1;}
    void setdate_2(QDate date_2){this ->date_2=date_2;}
    void setID(int id){this->id=id;}

    bool ajouter();
    QSqlQueryModel* afficher();
bool supprimer(int);

bool modifier(int,QDate,QDate);
private:
int id;
QDate date_1, date_2;
};
#endif // ABONNEMENT_H
