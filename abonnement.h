#ifndef ABONNEMENT_H
#define ABONNEMENT_H
#include<QString>
#include<QSqlQueryModel>

class abonnement
{
public:
    abonnement();
   abonnement(QString n);
    abonnement(int,QString,QString,QString,float,int);
    bool ajouter();
    bool supprimer(int ID);
    bool modifier(int ID);
QSqlQueryModel* afficher();
QSqlQueryModel* recherche(QString type);
QSqlQueryModel* meilleur_prix();
QSqlQueryModel* meilleur_nombres();
QSqlQueryModel* id_select(int ID);

bool promotion_etudiant(QString type);
bool promotion_client(QString type);
bool promotion_Admistration(QString type);

QSqlQueryModel* id_select2(int ID);










private:
       int id;
    QString type_abonnment;
    QString date_debut_abonnement;
      QString date_fin_abonnment;
        float prix;
        int nb_abonnement;



};

#endif // ABONNEMENT_H
