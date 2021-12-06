#include "abonnement.h"
abonnement::abonnement(int id,QDate date_1,QDate date_2)
{
  this->id=id;
  this->date_1=date_1;
  this->date_2=date_2;

}
bool  abonnement::ajouter()
{
 QSqlQuery query;
 QString res = QString::number(id);

 query.prepare("insert into abonnement (id, date_1, date_2)" "values (:id, :date_1, :date_2)");

 query.bindValue(":id" ,res);
 query.bindValue(":date_1" ,date_1);
 query.bindValue(":date_2" ,date_2);
 return query.exec();


}
QSqlQueryModel * abonnement::afficher()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from abonnement");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("date_1"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("date_2"));
 return model;


}
bool abonnement::supprimer(int id)
{
    QSqlQuery query;
    QString res = QString::number(id);

    query.prepare("Delete from abonnement where ID= :id");

    query.bindValue(":id",res);
return query.exec();
}
bool abonnement::modifier(int id,QDate date_1,QDate date_2)
{

       QSqlQuery query;
       QString id_l_string=QString::number(id);

    query.prepare("UPDATE ligne SET   date_1= :date_1 , date_2= :date_2  WHERE id_l= :id ");
    query.bindValue(":id",id);
    query.bindValue(":date_1",date_1);
    query.bindValue(":date_2",date_2);


    return query.exec();
     }
