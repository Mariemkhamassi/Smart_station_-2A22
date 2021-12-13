#include "abonnement.h"
#include<QString>
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
abonnement::abonnement()
{
    id=0;
        type_abonnment="";
        date_debut_abonnement="";
        date_fin_abonnment="";
 prix=0;
  nb_abonnement=0;
}
 abonnement::abonnement(int i,QString t,QString db,QString df,float p,int n)
 {
     id=i;
         type_abonnment=t;
         date_debut_abonnement=db;
         date_fin_abonnment=df;
  prix=p;
   nb_abonnement=n;


 }
bool abonnement::ajouter()
{


         QString run= QString::number(id);
         QString runs= QString::number(nb_abonnement);
         QString ren= QString::number(prix);
         QSqlQuery query;
        query.prepare("INSERT INTO ABONNEMENT (ID,TYPE_ABONNEMENT,PRIX,DATE_DEBUT,DATE_FIN,NB_ABONNEMENT) VALUES (:id,:type,:p,:db,:df,:nb)");
     query.bindValue(":id",run);
     query.bindValue(":type",type_abonnment );
       query.bindValue(":p",ren);
       query.bindValue(":db",  date_debut_abonnement);
       query.bindValue(":df",date_fin_abonnment);
       query.bindValue(":nb",runs);
        return query.exec();


 }

bool abonnement::modifier(int ID)
{
    QString rid=QString::number(ID);
        QString rnb=QString::number(nb_abonnement);
        QString runs= QString::number(prix);
        QSqlQuery query;
           query.prepare(QString("update Abonnement set TYPE_ABONNEMENT=:type,PRIX=:prix,DATE_DEBUT=:db,DATE_FIN=:df,NB_ABONNEMENT=:nb where ID=:id"));

                      query.bindValue(":id",rid);
           query.bindValue(":type",type_abonnment);
           query.bindValue(":db", date_debut_abonnement);

           query.bindValue(":df", date_fin_abonnment);
           query.bindValue(":prix",runs);
           query.bindValue(":nb",rnb);

         return  query.exec();





}
QSqlQueryModel* abonnement::afficher()
{
    QSqlQuery query;
        QSqlQueryModel* model= new QSqlQueryModel();

        query.prepare("SELECT* FROM ABONNEMENT ");
              query.exec();
              model->setQuery(query);


       return model;
}
bool abonnement::supprimer(int ID)
{
QString rid=QString::number(ID);
    QSqlQuery query;
    query.prepare("DELETE FROM ABONNEMENT WHERE ID=:id ");
    query.bindValue(":id", rid);

    return query.exec();

}

QSqlQueryModel* abonnement::recherche(QString type)
{  QSqlQuery query;
    QSqlQueryModel* model= new QSqlQueryModel();

    query.prepare("SELECT* FROM ABONNEMENT WHERE TYPE_ABONNEMENT=:type  ");
    query.bindValue(":type", type);

    query.exec();
          model->setQuery(query);


   return model;






}
QSqlQueryModel* abonnement::meilleur_prix()
{
    QSqlQuery query;
        QSqlQueryModel* model= new QSqlQueryModel();

        query.prepare("SELECT ID,TYPE_ABONNEMENT,DATE_DEBUT,DATE_FIN,PRIX FROM ABONNEMENT ORDER BY PRIX DESC ");

        query.exec();
              model->setQuery(query);


       return model;


}
QSqlQueryModel* abonnement::meilleur_nombres()
{
    QSqlQuery query;
        QSqlQueryModel* model= new QSqlQueryModel();

        query.prepare("SELECT ID,TYPE_ABONNEMENT,DATE_DEBUT,DATE_FIN,NB_ABONNEMENT FROM ABONNEMENT ORDER BY NB_ABONNEMENT DESC  ");

        query.exec();
              model->setQuery(query);


       return model;


}

QSqlQueryModel* abonnement::id_select(int ID)
{
    QSqlQuery query;
        QSqlQueryModel* model= new QSqlQueryModel();
QString rid=QString::number(ID);
        query.prepare("SELECT *FROM ABONNEMENT WHERE ID=:id  ");
query.bindValue(":id", rid);
        query.exec();
              model->setQuery(query);


       return model;





}
bool abonnement::promotion_etudiant(QString type)
{
    QSqlQuery query;
       query.prepare(QString("UPDATE ABONNEMENT SET PRIX=PRIX*0.3 WHERE TYPE_ABONNEMENT=:type"));
query.bindValue(":type", type);
return query.exec();



}
bool abonnement::promotion_client(QString type)
{
    QSqlQuery query;
       query.prepare(QString("update Abonnement set PRIX=PRIX*0.2 where TYPE_ABONNEMENT=:type"));
query.bindValue(":type", type);
return query.exec();



}
bool abonnement::promotion_Admistration(QString type)
{
    QSqlQuery query;
       query.prepare(QString("update Abonnement set PRIX=PRIX*0.35 where TYPE_ABONNEMENT=:type"));
query.bindValue(":type", type);
 return query.exec();



 }
QSqlQueryModel* abonnement::id_select2(int ID)
{
    QSqlQuery query;
        QSqlQueryModel* model= new QSqlQueryModel();
QString rid=QString::number(ID);
        query.prepare("SELECT ID,PRIX FROM ABONNEMENT WHERE ID=:id  ");
query.bindValue(":id", rid);
        query.exec();
              model->setQuery(query);


       return model;



}
