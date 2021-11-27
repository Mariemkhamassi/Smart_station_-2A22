#include "ligne.h"


ligne::ligne(int id_l,QString depart,QString arrive,int kilometrage,QDate date_n)
{
 this->id_l=id_l;
 this->depart=depart;
 this->arrive=arrive;
 this->kilometrage=kilometrage;
 this->date_n=date_n;


}
bool  ligne::ajouter()
{
QSqlQuery query;
QString res = QString::number(id_l);

query.prepare("insert into ligne (id_l, depart, arrive, kilometrage, date_n)" "values (:id_l, :depart, :arrive, :kilometrage, :date_n)");

query.bindValue(":id_l" ,res);
query.bindValue(":depart" ,depart);
query.bindValue(":arrive" ,arrive);
query.bindValue(":kilometrage" ,kilometrage);
query.bindValue(":date_n" ,date_n);

return query.exec();


}
QSqlQueryModel * ligne::afficher()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from ligne");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_l"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("depart"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("arrive"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("kilometrage"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("date_n"));
return model;
}
QSqlQueryModel * ligne::afficherTri(QString critere)
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from ligne order by "+critere);
model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_l"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("depart"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("arrive"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("kilometrage"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("date_n"));
return model;
}
QSqlQueryModel * ligne::afficherRech(QString rech,QString critere)
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from ligne where "+critere+" like '"+rech+"%'");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_l"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("depart"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("arrive"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("kilometrage"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("date_n"));
return model;
}
bool ligne::supprimer(int id_l)

{
  QSqlQuery query;
   QString res = QString::number(id_l);

   query.prepare("Delete from ligne where id_l= :id_l");

   query.bindValue(":id_l",res);

return query.exec();
}

bool ligne::modifier(int id_l,QString depart,QString arrive,int kilometrage)
{

       QSqlQuery query;
       QString id_l_string=QString::number(id_l);

    query.prepare("UPDATE ligne SET  depart= :depart , arrive= :arrive , kilometrage= :kilometrage  WHERE id_l= :id_l ");
    query.bindValue(":id_l",id_l);
    query.bindValue(":depart",depart);
    query.bindValue(":arrive",arrive);
    query.bindValue(":kilometrage",kilometrage);

    return query.exec();
     }
bool ligne::recherche_mod(int)
{ }
