#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "abonnement.h"
#include <QIntValidator>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ajoutid_l->setValidator(new QIntValidator(0, 9999999,  this));
    ui->tableView->setModel(Etmp.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_ajouter_clicked()
{
    int id=ui->ajoutid_l->text().toInt();
    QDate date_1=ui->dateEdit->date();
    QDate date_2=ui->dateEdit_2->date();
    abonnement E(id,date_1,date_2);

    bool test=E.ajouter();
    if(test)
    {
          QMessageBox::information(nullptr, QObject::tr("OK") ,
                                   QObject::tr("Ajout effectué "
                                               "Clicked Cancel to exit.") , QMessageBox::Cancel);
    }
    else
          QMessageBox::critical(nullptr, QObject::tr("not OK") ,
                                   QObject::tr("Ajout non effectué "
                                               "Clicked Cancel to exit.") , QMessageBox::Cancel);
}

void MainWindow::on_pb_supprimer_2_clicked()
{
    int id=ui->ajoutid_l->text().toInt();
    bool test=Etmp.supprimer(id);
    if(test)
    {
          QMessageBox::information(nullptr, QObject::tr("OK") ,
                                   QObject::tr("Supression effectué "
                                               "Clicked Cancel to exit.") , QMessageBox::Cancel);
    }
    else
          QMessageBox::critical(nullptr, QObject::tr("not OK") ,
                                   QObject::tr("Suppression non effectué "
                                               "Clicked Cancel to exit.") , QMessageBox::Cancel);
}

void MainWindow::on_Modifier_clicked()
{
    abonnement l;
     int id=ui->ajoutid_l->text().toInt();
     QDate date_1=ui->dateEdit->date();
     QDate date_2=ui->dateEdit_2->date();

    bool test= l.modifier(id,date_1,date_2);
     QMessageBox msg;
    if(test)
    {    ui->tableView->setModel(l.afficher());
                    msg.setText("modifie avec succés");

                    }
                    else
                    {
                    msg.setText("Echec au niveau de la modif ");
                    }
                    msg.exec();

                ui->ajoutid_l->clear();
                ui->dateEdit->clear();
                ui->dateEdit_2->clear();

}
