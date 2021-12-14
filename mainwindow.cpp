#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ligne.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QValidator>
#include <QMap>
#include <QStyle>
#include <emp.h>
#include "billet.h"
#include<QSqlDatabase>
#include<QSqlQuery>
#include <QPixmap>
#include<QFile>
#include<QtDebug>
#include<QIODevice>
#include<QPainter>
#include <QIntValidator>
#include <QFileDialog>
#include<QTextStream>
#include "exel.h"
#include<QtGui>
#include "qcustomplot.h"
#include "statistiques.h"
#include "station.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QSystemTrayIcon>
#include <QTextStream>
#include <QPrinter>
#include <QTextDocument>
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
    int ret=a.connect_arduino();
          switch (ret) {
          case(0):qDebug()<<"arduino is available and connected to :"<<a.getarduino_port_name();
              break;
          case(1):qDebug()<<"arduino is available but not connected to :"<<a.getarduino_port_name();
              break;
          case(-1):qDebug()<<"arduino is not available";
          }
    QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));

    ui->quickWidget->show();
    ui->ajoutid_l->setValidator(new QIntValidator(0, 999999,  this));
    ui->ajout_kilometrage->setValidator(new QIntValidator(0, 999999,  this));
    ui->tableView->setModel(l.afficher());
    makePolt();
    makePolt1();

    ui->tableBus->setModel(bu.afficher());//affecter le modele qu'on a creé sur la tableBus
    QIntValidator *roll = new QIntValidator(10000000,99999999);
    ui->id->setValidator(roll);
    ui->idSupp->setValidator(roll);
    if(bu.compterBus()>15){
        QSystemTrayIcon* notifier = new QSystemTrayIcon(this);
                        notifier->setIcon(QIcon(""));
                         notifier->show();
                         notifier->showMessage("Il y a plus de 15 bus","Alerte!!!",QSystemTrayIcon::Critical,10000);
                         //mariem
                         QStringList list=(QStringList()<<"Chauffeur"<<"Responsable RH");
                         ui->comboBox->addItems(list);
                         ui->tableView->setModel(ajtmp.afficher());
                             ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                     }

//station
    ui->lineEdit_5->setValidator(new QIntValidator(0,999999999,this) );
       ui->comboBox_5->addItem("Etudiant");
       ui->comboBox_5->addItem("Client");
       ui->comboBox_5->addItem("Adminstration");
       ui->comboBox_7->addItem("Etudiant");
       ui->comboBox_7->addItem("Client");
       ui->comboBox_7->addItem("Adminstration");

       ui->comboBox_10->addItem("Etudiant");
       ui->comboBox_10->addItem("Client");
       ui->comboBox_10->addItem("Adminstration");







       QSqlQuery query;

       QSqlQueryModel* model= new QSqlQueryModel();

           query.prepare("SELECT ID FROM ABONNEMENT  ");
                 query.exec();
                 model->setQuery(query);




       ui->comboBox_6->setModel(model);
       ui->comboBox_8->setModel(model);
    ui->comboBox_9->setModel(model);
   ui->comboBox_11->setModel(model);
   ui->comboBox_12->addItem("Etudiant");
   ui->comboBox_9->addItem("Client");
   ui->comboBox_9->addItem("Adminstration");


    }



MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::update_label()
{
data=a.read_from_arduino();
if (data == "1")
  {
    QMessageBox::information(nullptr, QObject::tr("Alert"),
    QObject::tr("mouvement detecté. \n"
                 "Click Cancel to exit. "), QMessageBox::Cancel);
    l.incr();
    a.write_to_arduino("2");
    QSqlQuery q("select nbr from nbr");
    while(q.next())ui->labnbr->setText(q.value(0).toString());
}
}
void MainWindow::makePolt()//Statistique mainwindow.cpp//
{
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->customPlot->setBackground(QBrush(gradient));
    QCPBars *regen = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    regen->setAntialiased(false);
    regen->setStackingGap(1);
    regen->setName("Stat pandoud");
    regen->setPen(QPen(QColor(0, 168, 140).lighter(130)));
    regen->setBrush(QColor(0, 168, 140));


    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 ;

    labels << "Kilometrage >10 " << "Kilometrage <10 " ;
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->customPlot->xAxis->setTicker(textTicker);
    ui->customPlot->xAxis->setTickLabelRotation(60);
    ui->customPlot->xAxis->setSubTicks(false);
    ui->customPlot->xAxis->setTickLength(0, 4);
    ui->customPlot->xAxis->setRange(0, 8);
    ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->xAxis->grid()->setVisible(true);
    ui->customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->customPlot->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    ui->customPlot->yAxis->setRange(0,20);
    ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
    ui->customPlot->yAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->yAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot->yAxis->setLabelColor(Qt::white);
    ui->customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    QVector<double> regenData;
int nbr=0;

int he=0;
QSqlQuery query1("select count(*) from ligne where kilometrage < 10");
while (query1.next()) {

                        he = query1.value(0).toInt();

                                                    }

    QSqlQuery query2("select count(*) from ligne where kilometrage > 10");
    while (query2.next()) {
                           nbr = query2.value(0).toInt();

                             }
    regenData << nbr << he ;
    regen->setData(ticks, regenData);

    // setup legend:
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->customPlot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

}

void MainWindow::on_ajouter_clicked()
{
    int id_l=ui->ajoutid_l->text().toInt();
    QString depart=ui->ajout_depart->text();
    QString arrive=ui->ajout_arrive->text();
    int kilometrage=ui->ajout_kilometrage->text().toInt();
    QDate date_n=ui->dateEdit->date();


    ligne l(id_l,depart,arrive,kilometrage,date_n);

    bool test=l.ajouter();
    if(test)
    {
        ui->tableView->setModel(l.afficher());
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
    int id_l=ui->ajoutid_l1->text().toInt();
    bool test=l.supprimer(id_l);
    if(test)
    {

        ui->tableView->setModel(l.afficher());
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
    ligne l;
     int id_l=ui->ajoutid_l->text().toInt();
     QString depart=ui->ajout_depart->text();
     QString arrive=ui->ajout_arrive->text();
     int kilometrage=ui->ajout_kilometrage->text().toInt();

    bool test= l.modifier(id_l,depart,arrive,kilometrage);
     QMessageBox msg;
    if(test)
    {    ui->tableView->setModel(l.afficher());
                    msg.setText("modifie avec succés");

                    }
                    else
                    {
                    msg.setText("Echec au niveau de la modification ");
                    }
                    msg.exec();

                ui->ajoutid_l->clear();
                ui->ajout_depart->clear();
                ui->ajout_arrive->clear();
                ui->ajout_kilometrage->clear();

}



void MainWindow::on_recherche_mod_clicked()
{
    QSqlQuery query;
    query.prepare("select depart, arrive, kilometrage from ligne where id_l=?;");
    query.addBindValue(ui->ajoutid_l->text());
    if(query.exec())
       {
        while(query.next())
         {

    ui->ajout_arrive->setText(query.value(1).toString());
    ui->ajout_depart->setText(query.value(0).toString());
    ui->ajout_kilometrage->setText(query.value(2).toString());
    ui->dateEdit->setDate(query.value(3).toDate());

            }
        }


}


void MainWindow::on_pushButton_clicked()
{
    ui->tableView->setModel(l.afficherRech(ui->lineEditRech->text(),ui->comboBoxRech->currentText()));

}

void MainWindow::on_pushButton_4_clicked()
{
     ui->tableView->setModel(l.afficherTri(ui->comboBoxTri->currentText()));
}

void MainWindow::on_pushButton_3_clicked()
{
    QTableView *table;
         table = ui->tableView;

         QString filters("CSV files (*.csv);;All files (*.*)");
         QString defaultFilter("CSV files (*.csv)");
         QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                            filters, &defaultFilter);
         QFile file(fileName+".csv");

         QAbstractItemModel *model =  table->model();
         if (file.open(QFile::WriteOnly | QFile::Truncate)) {
             QTextStream data(&file);
             QStringList strList;
             for (int i = 0; i < model->columnCount(); i++) {
                 if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                     strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                 else
                     strList.append("");
             }
             data << strList.join(";") << "\n";
             for (int i = 0; i < model->rowCount(); i++) {
                 strList.clear();
                 for (int j = 0; j < model->columnCount(); j++) {

                     if (model->data(model->index(i, j)).toString().length() > 0)
                         strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                     else
                         strList.append("");
                 }
                 data << strList.join(";") + "\n";
             }
             file.close();
             QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
         }

}

void MainWindow::on_pushButton_9_clicked()
{
    if(ui->id->text()!=""){

        QString id=ui->id->text();
        QSqlQuery q("select * from bus where id="+id);
        while(q.next()){
        ui->marque->setText(q.value(1).toString());
        ui->kilometrage->setText(q.value(4).toString());
        ui->nbplaces->setText(q.value(3).toString());}
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    int id=ui->id->text().toInt();
    QString marque=ui->marque->text();
    QString datefct=ui->datefct->text();
    int nbplaces=ui->nbplaces->text().toInt();
    float kilometrage=ui->kilometrage->text().toFloat();//preparation des informations a partir de la maquette
    if(id>=10000000 && id<=99999999 && kilometrage >= 0 && nbplaces >= 0){
    bus b(id,marque,datefct,nbplaces,kilometrage);//instanciation d'une instance bus avec tous les infos
    b.modifier(id);
     ui->tableBus->setModel(bu.afficher());
     QMessageBox::information(nullptr, QObject::tr("modification avec succes"),
                 QObject::tr(" successful.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);}
    else
        QMessageBox::critical(nullptr, QObject::tr("erreur de modification"),
                    QObject::tr(" erreur.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_2_clicked()
{
    int id=ui->id->text().toInt();
    QString marque=ui->marque->text();
    QString datefct=ui->datefct->text();
    int  nbplaces=ui->nbplaces->text().toInt();
    float kilometrage=ui->kilometrage->text().toFloat();//preparation des informations a partir de la maquette
if(id>=10000000 && id<=99999999 && kilometrage >= 0 && nbplaces >= 0)
{bus b(id,marque,datefct,nbplaces,kilometrage);//instanciation d'une instance bus avec tous les infos
    b.ajouter();
     ui->tableBus->setModel(bu.afficher());
     QMessageBox::information(nullptr, QObject::tr("ajout avec succes"),
                 QObject::tr(" successful.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
     if(bu.compterBus()>15){
         QSystemTrayIcon* notifier = new QSystemTrayIcon(this);
                         notifier->setIcon(QIcon(""));
                          notifier->show();
                          notifier->showMessage("Il y a plus de 15 bus","Alerte!!!",QSystemTrayIcon::Critical,10000);
     }

   }
else
    QMessageBox::critical(nullptr, QObject::tr("erreur d'ajout"),
                QObject::tr(" erreur.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_6_clicked()
{
    int id=ui->idSupp->text().toInt();//preparation du l'id qu'on veut supprimer
    bu.supprimer(id);
     ui->tableBus->setModel(bu.afficher());
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->tableBus->setModel(bu.afficherTri(ui->comboBoxTri_2->currentText()));
}

void MainWindow::on_pushButton_10_clicked()
{
    ui->tableBus->setModel(bu.afficherRech(ui->lineEditRech_2->text(),ui->comboBoxRech_2->currentText()));
}

void MainWindow::on_pushButton_12_clicked()
{
    QString strStream;
                      QTextStream out(&strStream);

                       const int rowCount = ui->tableBus->model()->rowCount();
                       const int columnCount = ui->tableBus->model()->columnCount();
                      out <<  "<html>\n"
                      "<head>\n"
                                       "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                       <<  QString("<title>%1</title>\n").arg("strTitle")
                                       <<  "</head>\n"
                                       "<body bgcolor=#ffffff link=#5000A0>\n"

                                      //     "<align='right'> " << datefich << "</align>"
                                       "<center> <H1>Liste des BUS</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                   // headers
                                   out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                   out<<"<cellspacing=10 cellpadding=3>";
                                   for (int column = 0; column < columnCount; column++)
                                       if (!ui->tableBus->isColumnHidden(column))
                                           out << QString("<th>%1</th>").arg(ui->tableBus->model()->headerData(column, Qt::Horizontal).toString());
                                   out << "</tr></thead>\n";

                                   // data table
                                   for (int row = 0; row < rowCount; row++) {
                                       out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                       for (int column = 0; column < columnCount; column++) {
                                           if (!ui->tableBus->isColumnHidden(column)) {
                                               QString data = ui->tableBus->model()->data(ui->tableBus->model()->index(row, column)).toString().simplified();
                                               out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                           }
                                       }
                                       out << "</tr>\n";
                                   }
                                   out <<  "</table> </center>\n"
                                       "</body>\n"
                                       "</html>\n";

                             QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                               if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                              QPrinter printer (QPrinter::PrinterResolution);
                               printer.setOutputFormat(QPrinter::PdfFormat);
                              printer.setPaperSize(QPrinter::A4);
                             printer.setOutputFileName(fileName);

                              QTextDocument doc;
                               doc.setHtml(strStream);
                               doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                               doc.print(&printer);
}
void MainWindow::makePolt1()
{
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->customPlot_2->setBackground(QBrush(gradient));
    QCPBars *regen = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    regen->setAntialiased(false);
    regen->setStackingGap(1);
    regen->setName("Stat pandoud");
    regen->setPen(QPen(QColor(0, 168, 140).lighter(130)));
    regen->setBrush(QColor(0, 168, 140));


    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 ;

    labels << "kilometrage >100000 " << "kilometrage <100000 " ;
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->customPlot_2->xAxis->setTicker(textTicker);
    ui->customPlot_2->xAxis->setTickLabelRotation(60);
    ui->customPlot_2->xAxis->setSubTicks(false);
    ui->customPlot_2->xAxis->setTickLength(0, 4);
    ui->customPlot_2->xAxis->setRange(0, 8);
    ui->customPlot_2->xAxis->setBasePen(QPen(Qt::white));
    ui->customPlot_2->xAxis->setTickPen(QPen(Qt::white));
    ui->customPlot_2->xAxis->grid()->setVisible(true);
    ui->customPlot_2->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->customPlot_2->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot_2->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    ui->customPlot_2->yAxis->setRange(0,20);
    ui->customPlot_2->yAxis->setPadding(5); // a bit more space to the left border
    ui->customPlot_2->yAxis->setBasePen(QPen(Qt::white));
    ui->customPlot_2->yAxis->setTickPen(QPen(Qt::white));
    ui->customPlot_2->yAxis->setSubTickPen(QPen(Qt::white));
    ui->customPlot_2->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot_2->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot_2->yAxis->setLabelColor(Qt::white);
    ui->customPlot_2->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->customPlot_2->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    QVector<double> regenData;
int nbr=0;

int he=0;
QSqlQuery query1("select count(*) from bus where kilometrage > 100000 ");
while (query1.next()) {

                        he = query1.value(0).toInt();

                                                    }

    QSqlQuery query2("select count(*) from bus where kilometrage < 100000 ");
    while (query2.next()) {
                           nbr = query2.value(0).toInt();

                             }
    regenData << he << nbr ;
    regen->setData(ticks, regenData);

    // setup legend:
    ui->customPlot_2->legend->setVisible(true);
    ui->customPlot_2->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->customPlot_2->legend->setBrush(QColor(255, 255, 255, 100));
    ui->customPlot_2->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot_2->legend->setFont(legendFont);
    ui->customPlot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);


}

void MainWindow::on_pushButton_13_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_14_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_15_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}



//employe
void MainWindow::on_pushButton_19_clicked()//ajout
{

    QString nom=ui->l_nom->text();
    QString prenom=ui->l_prenom->text() ;
    QString cb=ui->comboBox->currentText() ;
    int sal =ui->l_sal_2->text().toInt();


    emp R(nom, prenom,cb,sal);
                bool test=R.ajouter();
                ui->tableView_2->setModel(ajtmp.afficher());
                QMessageBox msgBox;
                if (test)
                {
                    ui->tableView_2->setModel(ajtmp.afficher());
                    msgBox.setText("Ajout avec succés.");
                    msgBox.exec();
                }
}

void MainWindow::on_pushButton_20_clicked()//modifier
{ ui->tableView_2->setModel(ajtmp.afficher());
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QString id=ui->l_id->text();
    QString nom=ui->l_nom->text();
    QString prenom=ui->l_prenom->text();
    QString cb = ui->comboBox->currentText();
    QString sal=ui->l_sal_2->text();

    emp e;
    bool test=e.modifier(nom,prenom,cb,sal,id);
    QMessageBox msBox;
    if(test)
    {
        ui->tableView_2->setModel(e.afficher());
        ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        msBox.setText("modification reussite");
        msBox.exec();
    }
    else
    {
        msBox.setText("ERREUR");
        msBox.exec();}

}

void MainWindow::on_pushButton_21_clicked()//supprimer
{ QMessageBox msgBox ;
    int cc = ui->l_id->text().toInt();
        bool test=ajtmp.supprimer(cc);
        if(test)
        {ui->tableView_2->setModel(ajtmp.afficher());//refresh
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

void MainWindow::on_pushButton_23_clicked()//tri
{
    QMessageBox msgBox ;
    QSqlQueryModel *model = new QSqlQueryModel();


             switch (ui->TRIER->currentIndex()) {
             case 0:
                 model->setQuery("select * from EMPLOYE order by NOM ASC");
                 model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
                 model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
                 model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
                 model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
                 model->setHeaderData(4, Qt::Horizontal, QObject::tr("SALAIRE"));

                 break;
             case 1:
                 model->setQuery("select * from EMPLOYE order by ID ASC");
                 model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
                 model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
                 model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
                 model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
                 model->setHeaderData(4, Qt::Horizontal, QObject::tr("SALAIRE"));
             case 2:
                 model->setQuery("select * from EMPLOYE order by PRENOM");
                 model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
                 model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
                 model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
                 model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
                 model->setHeaderData(4, Qt::Horizontal, QObject::tr("SALAIRE"));
                 break;
             }
             ui->tableView_2->setModel(model);
             ui->tableView_2->show();
             msgBox.setText("Tri avec succés.");
             msgBox.exec();
}

void MainWindow::on_pushButton_22_clicked()//recherche
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

        ui->tableView_2->setModel(model);
           ui->tableView_2->show();
           msgBox.setText(" trouvé.");
           msgBox.exec();
           ui->rech->clear();
}


void MainWindow::on_pushButton_25_clicked()//mailling
{
    QString link="https://mail.google.com/mail/u/0/#inbox?compose=new";
    QDesktopServices::openUrl(link);
}

void MainWindow::on_pushButton_24_clicked()//stat
{
    QSqlQuery q,q1;
    q.prepare("select count(id),genre from EMPLOYE group by type;");
    q1.prepare("select count(id) from EMPLOYE;");
    q.exec();
    q1.exec();
    q1.next();
    int total=q1.value(0).toInt();
    while(q.next()){
        if(q.value(1).toString().compare("chauffeur")==0)ui->progressBar->setValue(q.value(0).toInt()*100/total);
        if(q.value(1).toString().compare("responsable RH")==0)ui->progressBar_2->setValue(q.value(0).toInt()*100/total);
    }
}

void MainWindow::on_tableView_2_clicked(const QModelIndex &index)
{
    QString val=ui->tableView_2->model()->data(index).toString();

        QSqlQuery qry;
        qry.prepare("select * from EMPLOYE where ID='"+val+"'  " );

        if(qry.exec())
        {
            while(qry.next())
            {
                ui->l_id->setText(qry.value(0).toString());

                ui->l_nom->setText(qry.value(1).toString());
                ui->l_prenom->setText(qry.value(2).toString());
                ui->l_sal_2->setText(qry.value(4).toString());
                ui->comboBox->setCurrentText(qry.value(3).toString());





            }
        }
}
void MainWindow::on_comboBox_3_activated(const QString &arg1)
 {
     if(arg1!="chauffeur" && arg1!="responsable RH"){
         ui->pushButton_19->setDisabled(true);
     }else     ui->pushButton_19->setDisabled(false);
 }

void MainWindow::on_comboBox_2_activated(const QString &arg1)
 { if(arg1!="chauffeur" && arg1!="responsable RH"){
         ui->pushButton_20->setDisabled(true);
     }else     ui->pushButton_20->setDisabled(false);

 }




//abdou
void MainWindow::on_pushButton_27_clicked()//ajouter
{
    int prix=ui->lineEdit_5->text().toInt();
    int num=ui->lineEdit_4->text().toInt();
  QString nom_station =ui->lineEdit_8->text();
        QString date_c =ui->lineEdit_6->text();
            QString date_ex =ui->lineEdit_7->text();
            billet b(num,prix,date_c,date_ex,nom_station);

            bool test=b.ajouter();
            if(test)



            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("Ajout successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

            else QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                                   QObject::tr("ajout non effectué.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_28_clicked()
{

}

void MainWindow::on_pushButton_29_clicked()
{
    QTableView *table;
         table = ui->tableView_3;

         QString filters("CSV files (*.csv);;All files (*.*)");
         QString defaultFilter("CSV files (*.csv)");
         QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                            filters, &defaultFilter);
         QFile file(fileName+".csv");

         QAbstractItemModel *model =  table->model();
         if (file.open(QFile::WriteOnly | QFile::Truncate)) {
             QTextStream data(&file);
             QStringList strList;
             for (int i = 0; i < model->columnCount(); i++) {
                 if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                     strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                 else
                     strList.append("");
             }
             data << strList.join(";") << "\n";
             for (int i = 0; i < model->rowCount(); i++) {
                 strList.clear();
                 for (int j = 0; j < model->columnCount(); j++) {

                     if (model->data(model->index(i, j)).toString().length() > 0)
                         strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                     else
                         strList.append("");
                 }
                 data << strList.join(";") + "\n";
             }
             file.close();
             QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
         }
}

void MainWindow::on_pushButton_exel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exportation en fichier Excel"), qApp->applicationDirPath (),
                                                        tr("Fichiers d'extension Excel (*.xls)"));
        if (fileName.isEmpty())
            return;

        EXCEL obj(fileName, "C:/Users/Motaz/Desktop/finale", ui->tableView_3);

        // you can change the column order and
        // choose which colum to export
        obj.addField(0, "num_billet", "char(20)");
        obj.addField(1, "date_creation", "char(20)");
        obj.addField(2, "date_exp", "char(20)");
         obj.addField(3, "nom_station", "char(20)");
          obj.addField(4, "Prix", "char(20)");



        int retVal = obj.export2Excel();

        if( retVal > 0)
        {
            QMessageBox::information(this, tr("FAIS!"),
                                     QString(tr("%1 enregistrements exportés!")).arg(retVal)
                                     );
        }
}

void MainWindow::on_pushButton_PDF_clicked()
{
    QString strStream;
        QTextStream out(&strStream);

        const int rowCount = ui->tableView_3->model()->rowCount();
        const int columnCount = ui->tableView_3->model()->columnCount();

        out <<  "<html>\n"
               "<head>\n"
               "<meta Content=\"Text/html; charset=Windows-1251\">\n"
            <<  QString("<title>%1</title>\n").arg("strTitle")
            <<  "</head>\n"
               "<body bgcolor=#ffffff link=#5000A0>\n"

               //     "<align='right'> " << datefich << "</align>"
               "<center> <H1>Liste des commandes </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

        // headers
        out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
        for (int column = 0; column < columnCount; column++)
            if (!ui->tableView->isColumnHidden(column))
                out << QString("<th>%1</th>").arg(ui->tableView_3->model()->headerData(column, Qt::Horizontal).toString());
        out << "</tr></thead>\n";

        // data table
        for (int row = 0; row < rowCount; row++)
        {
            out << "<tr> <td bkcolor=0>" << row + 1 << "</td>";
            for (int column = 0; column < columnCount; column++)
            {
                if (!ui->tableView_2->isColumnHidden(column))
                {
                    QString data = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, column)).toString().simplified();
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

void MainWindow::on_pushButton_30_clicked()
{

    int prix=ui->lineEdit_8->text().toInt();
    QString text=ui->lineEdit_9->text();
    int num_string=ui->lineEdit_12->text().toInt();

  QString nom_station =ui->lineEdit_14->text();
        QString date_c =ui->lineEditS->text();
            QString date_ex =ui->lineEdit_10->text();

    billet b(num_string,prix,date_c,date_ex,nom_station);
    bool test=b.controle_billet( text);
  if( test){


        ui->textBrowser_2->setText("Oui");
       }


    else {
        ui->textBrowser_2->setText("non");

        QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                                   QObject::tr("controle non effectué.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
    }



}

void MainWindow::on_pushButton_stat_clicked()
{
    statistiques *s=new statistiques();
       s->show();
}

void MainWindow::on_pushButton_33_clicked()
{
    int prix=ui->lineEdit_8->text().toInt();
    int num_string=ui->lineEdit_12->text().toInt();
  QString nom_station =ui->lineEdit_7->text();
        QString date_c =ui->lineEdit_13->text();
            QString date_ex =ui->lineEdit_14->text();
}

void MainWindow::on_pushButton_32_clicked()
{
    int prix=ui->lineEdit_8->text().toInt();
    int num_string=ui->lineEdit_12->text().toInt();
  QString nom_station =ui->lineEdit_7->text();
        QString date_c =ui->lineEdit_5->text();
            QString date_ex =ui->lineEdit_11->text();
}

void MainWindow::on_pushButton_34_clicked()
{
    QTableView *table;
         table = ui->tableView_3;

         QString filters("CSV files (*.csv);;All files (*.*)");
         QString defaultFilter("CSV files (*.csv)");
         QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                            filters, &defaultFilter);
         QFile file(fileName+".csv");

         QAbstractItemModel *model =  table->model();
         if (file.open(QFile::WriteOnly | QFile::Truncate)) {
             QTextStream data(&file);
             QStringList strList;
             for (int i = 0; i < model->columnCount(); i++) {
                 if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                     strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                 else
                     strList.append("");
             }
             data << strList.join(";") << "\n";
             for (int i = 0; i < model->rowCount(); i++) {
                 strList.clear();
                 for (int j = 0; j < model->columnCount(); j++) {

                     if (model->data(model->index(i, j)).toString().length() > 0)
                         strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                     else
                         strList.append("");
                 }
                 data << strList.join(";") + "\n";
             }
             file.close();
             QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
         }
}
void MainWindow::on_pushButton_17_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
//station





void MainWindow::on_pushButton_35_clicked()
{
    int id_s=ui->lineEdit->text().toInt();
    bool test=Etmp.supprimer(id_s);
    if(test)
    {
          ui->tableView_4->setModel(Etmp.afficher());
          QMessageBox::information(nullptr, QObject::tr("OK") ,
                                   QObject::tr("Supression effectué "
                                               "Clicked Cancel to exit.") , QMessageBox::Cancel);
    }
    else
          QMessageBox::critical(nullptr, QObject::tr("not OK") ,
                                   QObject::tr("Suppression non effectué "
                                               "Clicked Cancel to exit.") , QMessageBox::Cancel);
}

void MainWindow::on_pushButton_36_clicked()
{
    int id_s=ui->lineEdit_15->text().toInt();
    QString loc=ui->lineEdit_16->text();
    int nb_b=ui->lineEdit_17->text().toInt();
    station s(id_s ,loc ,nb_b);

    bool test=s.ajouter();
    if(test)
    {
        ui->tableView_4->setModel(Etmp.afficher());
          QMessageBox::information(nullptr, QObject::tr("OK") ,
                                   QObject::tr("Ajout effectué "
                                               "Clicked Cancel to exit.") , QMessageBox::Cancel);
    }
    else
          QMessageBox::critical(nullptr, QObject::tr("not OK") ,
                                   QObject::tr("Ajout non effectué "
                                               "Clicked Cancel to exit.") , QMessageBox::Cancel);
}

void MainWindow::on_pushButton_37_clicked()
{
    station s;
     int id_s=ui->lineEdit_18->text().toInt();
     QString loc=ui->lineEdit_19->text();
     int nb_b=ui->lineEdit_20->text().toInt();
     bool test= s.modifier(id_s,loc,nb_b);
     QMessageBox msg;
    if(test)
    {    ui->tableView_4->setModel(s.afficher());
                    msg.setText("modifie avec succés");

                    }
                    else
                    {
                    msg.setText("Echec au niveau de la modif ");
                    }
                    msg.exec();

                ui->lineEdit_18->clear();
                ui->lineEdit_19->clear();
                ui->lineEdit_20->clear();
}

void MainWindow::on_pushButton_38_clicked()
{ station s;
    ui->tableView_4->setModel(s.afficherRech(ui->lineEdit_21->text(),ui->comboBox->currentText()));

}


void MainWindow::on_pushButton_39_clicked()
{
    QString link="https://mail.google.com/mail/u/0/#inbox?compose=new";
    QDesktopServices::openUrl(link);
}

void MainWindow::on_pushButton_40_clicked()
{
    station s;
    ui->tableView->setModel(s.afficherTri(ui->comboBox_2->currentText()));
}



void MainWindow::on_pushButton_7_clicked()
{
    QString link="https://mail.google.com/mail/u/0/#inbox?compose=new";
    QDesktopServices::openUrl(link);
}

void MainWindow::on_pushButton_16_clicked()
{
 ui->stackedWidget->setCurrentIndex(4);
}










//abonnement:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void MainWindow::on_pushButton_41_clicked()
{
    QString type=ui->comboBox_5->currentText();
    QString debut_date=ui->lineEdit_23->text();
    int id=ui->lineEdit_22->text().toInt();
    int nba=ui->lineEdit_26->text().toInt();
    float prix=ui->lineEdit_25->text().toFloat();
 QString debut_fin=ui->lineEdit_24->text();
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

void MainWindow::on_pushButton_42_clicked()
{
    int  id=ui->comboBox_6->currentText().toInt();
        QString debut_date=ui->lineEdit_27->text();
        QString type=ui->comboBox_7->currentText();
        int nba=ui->lineEdit_30->text().toInt();
        float prix=ui->lineEdit_28->text().toFloat();
     QString debut_fin=ui->lineEdit_29->text();
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

void MainWindow::on_pushButton_43_clicked()
{
    int id=ui->comboBox_8->currentText().toInt();
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

void MainWindow::on_pushButton_44_clicked()
{
    QSqlQuery query;

    QSqlQueryModel* model= new QSqlQueryModel();

        query.prepare("SELECT ID FROM ABONNEMENT  ");
              query.exec();
              model->setQuery(query);




    ui->comboBox_6->setModel(model);
    ui->comboBox_8->setModel(model);
 ui->comboBox_10->setModel(model);
    abonnement A;
    ui->tableView_5->setModel(A.afficher());
}

void MainWindow::on_pushButton_46_clicked()
{

    QString type=ui->comboBox_9->currentText();
    abonnement A;
        ui->tableView_6->setModel(A.recherche(type));
}

void MainWindow::on_pushButton_50_clicked()
{
    ui->tableView_8->setModel(A.meilleur_prix());

}

void MainWindow::on_pushButton_51_clicked()
{
    ui->tableView_9->setModel(A.meilleur_nombres());
}

void MainWindow::on_pushButton_49_clicked()
{
    int  id=ui->comboBox_10->currentText().toInt();
    ui->tableView_7->setModel(A.id_select(id));
}

void MainWindow::on_pushButton_48_clicked()
{
    QString strStream;
       QTextStream out(&strStream);

       const int rowCount = ui->tableView_7->model()->rowCount();
       const int columnCount = ui->tableView_7->model()->columnCount(); // Collones de tableaux

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
           if (!ui->tableView_7->isColumnHidden(column))
               out << QString("<th>%1</th>").arg(ui->tableView_5->model()->headerData(column, Qt::Horizontal).toString());
       out << "</tr></thead>\n";

       // data table
       for (int row = 0; row < rowCount; row++)
       {
           out << "<tr> <td bkcolor=0>" << row + 1 << "</td>";
           for (int column = 0; column < columnCount; column++)
           {
               if (!ui->tableView_7->isColumnHidden(column))
               {
                   QString data = ui->tableView_7->model()->data(ui->tableView_7->model()->index(row, column)).toString().simplified();
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

void MainWindow::on_pushButton_47_clicked()
{
    QPrinter printer;
         printer.setPrinterName("Imprimante");
         QPrintDialog dialog(&printer, this);
         if (dialog.exec() == QDialog::Rejected) return;
         ui->tableView_5->render(&printer);
}

void MainWindow::on_pushButton_45_clicked()
{
    QString link="https://mail.google.com/mail/u/0/#inbox?compose=new";
    QDesktopServices::openUrl(link);
}

void MainWindow::on_pushButton_52_clicked()
{
    QString type=ui->comboBox_9->currentText();
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

void MainWindow::on_pushButton_53_clicked()
{
    QString type=ui->comboBox_9->currentText();
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

void MainWindow::on_pushButton_54_clicked()
{
    QString type=ui->comboBox_9->currentText();
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
 }
}

void MainWindow::on_pushButton_55_clicked()
{
    int id=ui->comboBox_11->currentText().toInt();
        ui->tableView_10->setModel(A.id_select2(id));
}

void MainWindow::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}
