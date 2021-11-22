
#include<QString>
#include<QSqlQueryModel>
#include <QDate>
class emp
{int id ;
    QString nom , prenom  ,type;
    int sal ;
public:
    emp();
    emp(QString,QString,QString,int);
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * tri();

    bool supprimer(int) ;

    bool modifier(QString, QString, QString,QString,QString);
    ~emp (){}
};


