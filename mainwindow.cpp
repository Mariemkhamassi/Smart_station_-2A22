#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QTextStream>
#include<QFileDialog>
#include <QPrinter>
#include <QTextDocument>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
     makePolt();
    ui->tableBus->setModel(bu.afficher());//affecter le modele qu'on a creé sur la tableBus
    QIntValidator *roll = new QIntValidator(10000000,99999999);
    ui->id->setValidator(roll);
    ui->idSupp->setValidator(roll);
    if(bu.compterBus()>15){
        QSystemTrayIcon* notifier = new QSystemTrayIcon(this);
                        notifier->setIcon(QIcon(""));
                         notifier->show();
                         notifier->showMessage("Il y a plus de 15 bus","Alerte!!!",QSystemTrayIcon::Critical,10000);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
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

void MainWindow::on_pushButton_2_clicked()
{
    int id=ui->idSupp->text().toInt();//preparation du l'id qu'on veut supprimer
    bu.supprimer(id);
     ui->tableBus->setModel(bu.afficher());
}

void MainWindow::on_pushButton_3_clicked()
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

void MainWindow::on_pushButton_5_clicked()
{
    ui->tableBus->setModel(bu.afficherTri(ui->comboBoxTri->currentText()));
}

void MainWindow::on_pushButton_4_clicked()
{
   ui->tableBus->setModel(bu.afficherRech(ui->lineEditRech->text(),ui->comboBoxRech->currentText()));
}

void MainWindow::on_pushButton_6_clicked()
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

void MainWindow::on_pushButton_7_clicked()
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
void MainWindow::makePolt()
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

    labels << "kilometrage >100000 " << "kilometrage <100000 " ;
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
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->customPlot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);


}
