#include "billet.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<iostream>
#include<QMessageBox>
#include <QSqlDatabase>
#include "connection.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <mainwindow.h>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>







billet::billet()
{
prix=0;   ;num=0;nom_station="";date_c="";date_ex="";
}
billet:: billet (int n,int p ,QString dc,QString dx ,QString noms  )

{
    num=n;
    prix=p;

    date_c=dc;
    date_ex=dx;
    nom_station=noms ;

}

//mrigel



bool billet ::ajouter(){



    QSqlQuery query;
    QString num_string =QString::number(num) ;
    QString prix_string= QString::number(prix) ;





    query.prepare("INSERT INTO BILLET ( NUM_BILLET,DATE_CREATION,DATE_EXPIRATION,NOM_STATION,PRIX)"
    "VALUES ( :num_billet,:date_creation,:date_expiration,:nom_station,:prix)");

       query.bindValue(":num_billet",num_string);
         query.bindValue(":date_creation" ,date_c);
               query.bindValue (":date_expiration",date_ex);
           query.bindValue(":nom_station",nom_station);
            query.bindValue(":prix",prix_string);


           return query.exec();

}
QSqlQueryModel* billet::afficher(){
    
    

}


bool billet :: update_billet (){

    QSqlQuery query;
    QString num_string =QString::number(num) ;
    QString prix_string= QString::number(prix) ;





    query.prepare("UPDATE billet SET date_expiration='"+date_ex+"' WHERE (num_billet='"+num_string+"')");


       query.bindValue(":num_billet",num_string);
         query.bindValue(":date_creation" ,date_c);
               query.bindValue (":date_expiration",date_ex);
           query.bindValue(":nom_station",nom_station);
            query.bindValue(":prix",prix_string);

 return query.exec();




}

bool billet :: update_billet2 (){

    QSqlQuery query;
    QString num_string =QString::number(num) ;
    QString prix_string= QString::number(prix) ;





    query.prepare("UPDATE billet SET date_expiration='"+date_ex+"' WHERE (date_creation='"+date_c+"')");


       query.bindValue(":num_billet",num_string);
         query.bindValue(":date_creation" ,date_c);
               query.bindValue (":date_expiration",date_ex);
           query.bindValue(":nom_station",nom_station);
            query.bindValue(":prix",prix_string);

 return query.exec();




}
bool billet :: supprimer(){

    QSqlQuery query;
    QString num_string =QString::number(num) ;
    QString prix_string= QString::number(prix) ;





    query.prepare("DELETE FROM BILLET  WHERE (date_creation='"+date_c+"')");


       query.bindValue(":num_billet",num_string);
         query.bindValue(":date_creation" ,date_c);
               query.bindValue (":date_expiration",date_ex);
           query.bindValue(":nom_station",nom_station);
            query.bindValue(":prix",prix_string);

 return query.exec();


}

bool billet :: controle_billet( QString text){

    QSqlQuery query;




bool test ;


 query.prepare("SELECT num_billet FROM BILLET  WHERE (num_billet='"+text+"')");


if (query.exec())
{ test= true ;
}
else {
    test=false ;
}



 return test ;


}

//CHECK numbillet
bool is_nan(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

int billet::calcul_region(QString region)
{
    QSqlQuery query;

    query.prepare("select * from BILLET where NOM_STATION='ariana' ");


    query.exec();
    int total=0;

    while(query.next())
    { total++;


    }
    return total;
}

