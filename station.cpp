#include "station.h"
#include<QDebug>

station::station(int id_s, QString loc, int nb_b)
{
 this->id_s=id_s;
 this->loc=loc;
 this->nb_b=nb_b;

}
bool  station::ajouter()
{
QSqlQuery query;
QString res = QString::number(id_s);

query.prepare("insert into station (id_s, loc, nb_b)" "values (:id_s, :loc, :nb_b)");

query.bindValue(":id_s" ,res);
query.bindValue(":loc",loc);
query.bindValue(":nb_b",nb_b);

return query.exec();


}



QSqlQueryModel * station::afficher()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from station");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_s"));
return model;

}

bool station::supprimer(int id_s)
{
   QSqlQuery query;
   QString res=QString::number(id_s);

   query.prepare("Delete from station where id_s= :id_s");

   query.bindValue(":id_s",res);
return query.exec();
}

bool station::modifier(int id_s,QString loc,int nb_b)
{

       QSqlQuery query;
       QString id_s_string=QString::number(id_s);

    query.prepare("UPDATE station SET   nb_b= :nb_b , loc= :loc  WHERE id_s= :id_s ");
    query.bindValue(":id_s",id_s);
    query.bindValue(":loc",loc);
    query.bindValue(":nb_b",nb_b);


    return query.exec();
     }

QSqlQueryModel* station::afficherRech(QString rech,QString critere)
{
    QSqlQueryModel* model=new QSqlQueryModel();//declaration du model
    model->setQuery("select * from station where "+critere+" like '"+rech+"%'");//requete qui va selecter du table
    return model;
}

QSqlQueryModel* station::afficherTri(QString critere)
{
    QSqlQueryModel* model=new QSqlQueryModel();//declaration du model
    model->setQuery("select * from station order by "+critere);//requete qui va selecter du table
    return model;
}
int station::compter_s(){
    int a=0;

    QSqlQuery q("select * from station");
    while (q.next()){
        a++;
    }

qDebug()<<a;
return a;

}
