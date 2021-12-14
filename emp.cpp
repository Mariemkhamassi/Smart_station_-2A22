#include "emp.h"
#include<QtSql/QSqlQuery>
#include<QVariant>
#include <QtSql/QSqlQueryModel>


emp::emp()
{nom="";prenom="";type="";   }
emp::emp(QString nom , QString prenom ,QString type , int sal )
{
  this->nom=nom;this->prenom=prenom;this->type=type;this->sal=sal;}
bool emp::ajouter()
{
    QSqlQuery query;
    query.prepare("insert into  EMPLOYE ( NOM, PRENOM,TYPE,SALAIRE)"
                  " values(:a,:b,:c,:d) ");
    query.bindValue(":a",nom);
    query.bindValue(":b",prenom);
    query.bindValue(":c",type);
    query.bindValue(":d",sal);

    return query.exec();
}
QSqlQueryModel * emp::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
          model->setQuery("select * from EMPLOYE");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("SALAIRE"));

          return model;

}
bool emp::supprimer(int cc)
{
    QSqlQuery query;
    int res3= cc;
    query.prepare("Delete from EMPLOYE where ID =?");
    query.addBindValue(res3);
    return    query.exec();
}
bool emp::modifier(QString nom, QString prenom,  QString type, QString sal,QString id)
{

    QSqlQuery query;
    query.prepare("update EMPLOYE  set NOM = '"+nom+"' , PRENOM = '"+prenom+"'   , TYPE = '"+type+"', SALAIRE = '"+sal+"'  where ID = '"+id+"' ");
          return query.exec();
}

QSqlQueryModel * emp::tri()
{
    QSqlQueryModel *model = new QSqlQueryModel();
          model->setQuery("select * from EMPLOYE order by NOM ASC");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("SALAIRE"));

          return model;

}






