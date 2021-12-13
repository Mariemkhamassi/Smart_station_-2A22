#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"abonnement.h"
#include<QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QtPrintSupport/QPrinter>
#include<QtPrintSupport/QPrintDialog>
#include<QFileInfo>
#include<QFileDialog>
#include <QTextEdit>
#include <QTextStream>
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
 ui->lineEdit_5->setValidator(new QIntValidator(0,999999999,this) );
    ui->comboBox->addItem("Etudiant");
    ui->comboBox->addItem("Client");
    ui->comboBox->addItem("Adminstration");
    ui->comboBox_3->addItem("Etudiant");
    ui->comboBox_3->addItem("Client");
    ui->comboBox_3->addItem("Adminstration");

    ui->comboBox_8->addItem("Etudiant");
    ui->comboBox_8->addItem("Client");
    ui->comboBox_8->addItem("Adminstration");







    QSqlQuery query;

    QSqlQueryModel* model= new QSqlQueryModel();

        query.prepare("SELECT ID FROM ABONNEMENT  ");
              query.exec();
              model->setQuery(query);




    ui->comboBox_2->setModel(model);
    ui->comboBox_4->setModel(model);
 ui->comboBox_6->setModel(model);
ui->comboBox_7->setModel(model);
ui->comboBox_5->addItem("Etudiant");
ui->comboBox_5->addItem("Client");
ui->comboBox_5->addItem("Adminstration");





}

MainWindow::~MainWindow()
{
    delete ui;
}

//////////////////////////////AJOUTER/////////////////////////////////
void MainWindow::on_pushButton_7_clicked()
{
    QString type=ui->comboBox->currentText();
    QString debut_date=ui->lineEdit_10->text();
    int id=ui->lineEdit_5->text().toInt();
    int nba=ui->lineEdit_19->text().toInt();
    float prix=ui->lineEdit_14->text().toFloat();
 QString debut_fin=ui->lineEdit_13->text();
    abonnement A(id,type,debut_date,debut_fin,prix,nba);
bool test=A.ajouter();


    if(test)
    {
          QMessageBox::information(nullptr, QObject::tr("OK"),
                      QObject::tr("Ajout effectue\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);



    }
    else
    {QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                              QObject::tr("Ajout non effectue\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

    }
}
//////////////////////////////Modifier/////////////////////////////////
void MainWindow::on_pushButton_8_clicked()
{  int  id=ui->comboBox_2->currentText().toInt();
    QString debut_date=ui->lineEdit_15->text();
    QString type=ui->comboBox_3->currentText();
    int nba=ui->lineEdit_6->text().toInt();
    float prix=ui->lineEdit_17->text().toFloat();
 QString debut_fin=ui->lineEdit_18->text();
    abonnement A(id,type,debut_date,debut_fin,prix,nba);

           bool  test=A.modifier(id);


             if(test)
             {
                     QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("update effectue\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);




             }
                 else
                     QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                 QObject::tr("update non effectue.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
}
//////////////////////////////Supprimer/////////////////////////////////
void MainWindow::on_pushButton_6_clicked()
{
    int id=ui->comboBox_4->currentText().toInt();
     bool test=A.supprimer(id);

    if(test)
    {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("Suppression effectue\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);




    }
        else
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                        QObject::tr("Suppression non effectue.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}
//////////////////////////////AFFICHER/////////////////////////////////
void MainWindow::on_pushButton_9_clicked()
{

    QSqlQuery query;

    QSqlQueryModel* model= new QSqlQueryModel();

        query.prepare("SELECT ID FROM ABONNEMENT  ");
              query.exec();
              model->setQuery(query);




    ui->comboBox_2->setModel(model);
    ui->comboBox_4->setModel(model);
 ui->comboBox_6->setModel(model);
    abonnement A;
    ui->tableView->setModel(A.afficher());
}
//////////////////////////////Recherche/////////////////////////////////
void MainWindow::on_pushButton_clicked()
{
    QString type=ui->comboBox_5->currentText();
    abonnement A;
        ui->tableView_2->setModel(A.recherche(type));
}
/////////////////////////////////////STATISTIQUE_prix//////////////////////////////////////
void MainWindow::on_pushButton_4_clicked()
{

ui->tableView_3->setModel(A.meilleur_prix());
}
/////////////////////////////////////STATISTIQUE_nombre d abonnement//////////////////////////////////////
void MainWindow::on_pushButton_10_clicked()
{
ui->tableView_4->setModel(A.meilleur_nombres());
}



void MainWindow::on_pushButton_12_clicked()
{
 int  id=ui->comboBox_6->currentText().toInt();
 ui->tableView_5->setModel(A.id_select(id));
}

void MainWindow::on_pushButton_11_clicked()
{
    QString strStream;
       QTextStream out(&strStream);

       const int rowCount = ui->tableView_5->model()->rowCount();
       const int columnCount = ui->tableView_5->model()->columnCount(); // Collones de tableaux

       out <<  "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
           <<  QString("<title>%1</title>\n").arg("strTitle")
           <<  "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"

           //     "<align='right'> " << datefich << "</align>"
           "<center> <H1>Liste Des Abonnements</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n\n\n";

       // headers
       out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
       for (int column = 0; column < columnCount; column++)
           if (!ui->tableView_5->isColumnHidden(column))
               out << QString("<th>%1</th>").arg(ui->tableView_5->model()->headerData(column, Qt::Horizontal).toString());
       out << "</tr></thead>\n";

       // data table
       for (int row = 0; row < rowCount; row++)
       {
           out << "<tr> <td bkcolor=0>" << row + 1 << "</td>";
           for (int column = 0; column < columnCount; column++)
           {
               if (!ui->tableView_5->isColumnHidden(column))
               {
                   QString data = ui->tableView_5->model()->data(ui->tableView_5->model()->index(row, column)).toString().simplified();
                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
               }
           }
           out << "</tr>\n";
       }
       out <<  "</table> </center>\n"
           "</body>\n"
           "</html>\n";

       QString fileName = QFileDialog::getSaveFileName((QWidget * )0, "Sauvegarder en PDF", QString(), "*.pdf");
       if (QFileInfo(fileName).suffix().isEmpty())
       {
           fileName.append(".pdf");
       }

       QPrinter printer (QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        QTextDocument doc;
        doc.setHtml(strStream);
        doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
        doc.print(&printer);
}

void MainWindow::on_pushButton_2_clicked()
{
    QPrinter printer;
         printer.setPrinterName("Imprimante");
         QPrintDialog dialog(&printer, this);
         if (dialog.exec() == QDialog::Rejected) return;
         ui->tableView->render(&printer);
}

void MainWindow::on_pushButton_5_clicked()
{

    QString link="https://mail.google.com/mail/u/0/#inbox?compose=new";
    QDesktopServices::openUrl(link);
}

void MainWindow::on_pushButton_3_clicked()
{QString type=ui->comboBox_8->currentText();
    if(type!="Client" && type!="Adminstration")
    {

    bool test=A.promotion_etudiant(type);
    if(test)
   {
           QMessageBox::information(nullptr, QObject::tr("OK"),
                       QObject::tr("Promotion effectue\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);




   }
       else
           QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                       QObject::tr("Promotion non effectue.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
 }
 }


void MainWindow::on_pushButton_13_clicked()
{QString type=ui->comboBox_8->currentText();
    if(type!="Etudiant" && type!="Adminstration")
    {
    bool test=A.promotion_client(type);

    if(test)
   {
           QMessageBox::information(nullptr, QObject::tr("OK"),
                       QObject::tr("Promotion effectue\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);




   }
       else
           QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                       QObject::tr("Promotion non effectue.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
   }
    }


void MainWindow::on_pushButton_14_clicked()
{
    QString type=ui->comboBox_8->currentText();
        if(type!="Etudiant" && type!="Client")
        {

    bool test=A.promotion_Admistration(type);
    if(test)
    {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("Promotion effectue\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);




    }
        else
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                        QObject::tr("Promotion non effectue.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
 }   }



void MainWindow::on_pushButton_15_clicked()
{
int id=ui->comboBox_7->currentText().toInt();
    ui->tableView_6->setModel(A.id_select2(id));
}
