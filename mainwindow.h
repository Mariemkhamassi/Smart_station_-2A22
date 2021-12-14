#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>
#include <QMainWindow>
#include "ligne.h"
#include "qcustomplot.h"
#include "arduino.h"
#include "bus.h"
#include "emp.h"
#include "billet.h"
#include "station.h"
#include "abonnement.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void makePolt();
    void makePolt1();
    void makePolt3();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:




    void on_ajouter_clicked();

    void on_Modifier_clicked();

    void on_pb_supprimer_2_clicked();

    void on_recherche_mod_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();
    void update_label();


    void on_pushButton_9_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_comboBox_2_activated(const QString &arg1);

    void on_pushButton_26_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_24_clicked();

    void on_tableView_2_clicked(const QModelIndex &index);


    //void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_comboBox_3_activated(const QString &arg1);

    void on_pushButton_15_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_exel_clicked();

    void on_pushButton_PDF_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_stat_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_32_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_35_clicked();

    void on_pushButton_36_clicked();

    void on_pushButton_37_clicked();

    void on_pushButton_38_clicked();

    void on_pushButton_39_clicked();

    void on_pushButton_40_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_41_clicked();

    void on_pushButton_42_clicked();

    void on_pushButton_43_clicked();

    void on_pushButton_44_clicked();

    void on_pushButton_46_clicked();

    void on_pushButton_50_clicked();

    void on_pushButton_51_clicked();

    void on_pushButton_49_clicked();

    void on_pushButton_48_clicked();

    void on_pushButton_47_clicked();

    void on_pushButton_45_clicked();

    void on_pushButton_52_clicked();

    void on_pushButton_53_clicked();

    void on_pushButton_54_clicked();

    void on_pushButton_55_clicked();

private:
    Ui::MainWindow *ui;
ligne  l;
arduino a;
QByteArray data;
bus bu;
emp ajtmp;
QSqlDatabase mydb;
station Etmp;
 abonnement A;
};
#endif // MAINWINDOW_H

