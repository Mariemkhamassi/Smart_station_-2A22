#include "statistiques.h"
#include "ui_statistiques.h"

statistiques::statistiques(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::statistiques)
{
    ui->setupUi(this);

    QPieSeries *series=new QPieSeries();

    series->append("ariana",tmpc.calcul_region("ariana"));
    series->append("sfax",tmpc.calcul_region("sfax"));
    series->append("jandouba",tmpc.calcul_region("jandouba"));
    series->append("mistir",tmpc.calcul_region("mistir"));



    QPieSlice *slice1=series->slices().at(1);
    slice1->setExploded(true);

    QChart *chart =new QChart();
    chart->addSeries(series);
    chart->setTitle("region");
    chart->setAnimationOptions(QChart::AllAnimations);
    QChartView *chartview=new QChartView(chart);

    this->setCentralWidget(chartview);
}

statistiques::~statistiques()
{
    delete ui;
}
