#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>
#include <QMainWindow>
#include "ligne.h"
#include "qcustomplot.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void makePolt();
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

private:
    Ui::MainWindow *ui;
ligne  l;
};
#endif // MAINWINDOW_H

