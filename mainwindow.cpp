#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ligne.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QValidator>
#include <QMap>
#include <QStyle>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));

    ui->quickWidget->show();
    ui->ajoutid_l->setValidator(new QIntValidator(0, 999999,  this));
    ui->ajout_kilometrage->setValidator(new QIntValidator(0, 999999,  this));
    ui->tableView->setModel(l.afficher());
    makePolt();
}


MainWindow::~MainWindow()
{
    delete ui;
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
