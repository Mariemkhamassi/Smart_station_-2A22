#ifndef BILLET_H
#define BILLET_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class billet
{
private:
    int num,prix;
    QString date_c ,date_ex,nom_station ;
public:
    billet();
    billet(int,int,QString,QString,QString);
int getid();
    int getnum();
    int getprix();
    QString getdate_c();
    QString getdate_ex();
    QString getnom_station();

    void setid(int);
    void setnum(int);
    void setprix(int);
    void setdate_c(QString);
    void setdate_ex(QString);
    void setnom_station (QString);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer();
    bool update_billet();
    bool update_billet2();
bool controle_billet( QString text);

bool is_nan() ;
bool stat_billet();
int calcul_region( QString );

};
#endif // BILLET_H
