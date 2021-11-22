#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include<QSqlQuery>
#include <QPdfWriter>
#include <QPainter>
#include <QPrinter>
#include <QDebug>
#include <QTextDocument>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList list=(QStringList()<<"Chauffeur"<<"Responsable RH"<<"Responsable de parc");
    ui->comboBox->addItems(list);
    ui->tableView->setModel(ajtmp.afficher());
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked() //ajout
{
    QString nom=ui->l_nom->text();
    QString prenom=ui->l_prenom->text() ;
    QString cb=ui->comboBox->currentText() ;
    int sal =ui->l_sal->text().toInt();


    emp R(nom, prenom,cb,sal);
                bool test=R.ajouter();
                ui->tableView->setModel(ajtmp.afficher());
                QMessageBox msgBox;
                if (test)
                {
                    ui->tableView->setModel(ajtmp.afficher());
                    msgBox.setText("Ajout avec succés.");
                    msgBox.exec();
                }
}

void MainWindow::on_pushButton_3_clicked() //suppression
{
    QMessageBox msgBox ;
        int cc = ui->l_id->text().toInt();
            bool test=ajtmp.supprimer(cc);
            if(test)
            {ui->tableView->setModel(ajtmp.afficher());//refresh
                /*QMessageBox::information(nullptr, QObject::tr("Supprime un dossier"),
                            QObject::tr(" Dossier supprimé.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel)*/
                msgBox.setText("Dossier supprimé.");
                msgBox.exec();

            }
            else
            {QMessageBox::critical(nullptr, QObject::tr("Supprimer failed "),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();

        QSqlQuery qry;
        qry.prepare("select * from EMPLOYE where ID='"+val+"'  " );

        if(qry.exec())
        {
            while(qry.next())
            {
                ui->l_id->setText(qry.value(0).toString());

                ui->l_nom->setText(qry.value(1).toString());
                ui->l_prenom->setText(qry.value(2).toString());
                ui->l_sal->setText(qry.value(4).toString());
                ui->comboBox->setCurrentText(qry.value(3).toString());





            }
        }
}

void MainWindow::on_pushButton_2_clicked() //modif
{
    ui->tableView->setModel(ajtmp.afficher());
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        QString id=ui->l_id->text();
        QString nom=ui->l_nom->text();
        QString prenom=ui->l_prenom->text();
        QString cb = ui->comboBox->currentText();
        QString sal=ui->l_sal->text();

        emp e;
        bool test=e.modifier(nom,prenom,cb,sal,id);
        QMessageBox msBox;
        if(test)
        {
            ui->tableView->setModel(e.afficher());
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            msBox.setText("modification reussite");
            msBox.exec();
        }
        else
        {
            msBox.setText("ERREUR");
            msBox.exec();}
}

void MainWindow::on_pushButton_4_clicked() //tri
{
    ui->tableView->setModel(ajtmp.tri());
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);}






void MainWindow::on_pushButton_6_clicked() //recherche
{
    QMessageBox msgBox ;
           QSqlQueryModel *model = new QSqlQueryModel();
           QString reff;
           reff = ui->rech->text();
           model->setQuery("Select * from COMPETITIONS where NOM = '"+reff+"' ");
           model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("prenom"));
           model->setHeaderData(4, Qt::Horizontal, QObject::tr("salaire"));

        ui->tableView->setModel(model);
           ui->tableView->show();
           msgBox.setText(" trouvé.");
           msgBox.exec();
           ui->rech->clear();
}

void MainWindow::PrintWidget(QWidget* widget)
{

  QPixmap pix(widget->size());
  QPainter painter(&pix);
  widget->render(&painter);
  painter.end();
  QPrinter printer(QPrinter::HighResolution);
  printer.setOrientation(QPrinter::Landscape);
  printer.setOutputFormat(QPrinter::PdfFormat);
  printer.setPaperSize(QPrinter::A4);
  printer.setOutputFileName("C:/Users/Mariem kamputere/test.pdf"); // will be in build folder

  painter.begin(&printer);
  double xscale = printer.pageRect().width() / double(pix.width());
  double yscale = printer.pageRect().height() / double(pix.height());
  double scale = qMin(xscale, yscale);
  painter.translate(printer.paperRect().x() + printer.pageRect().width() / 2,
                    printer.paperRect().y() + printer.pageRect().height() / 2);
  painter.scale(scale, scale);
  painter.translate(-widget->width() / 2, -widget->height() / 2);
  painter.drawPixmap(0, 0, pix);

QTextDocument doc;

doc.setHtml("htmlcontent");
doc.drawContents(&painter);

  painter.end();
}
void MainWindow::on_pushButton_7_clicked() //pdf
{
 PrintWidget(ui->tableView) ;
}
