#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>
#include <QMainWindow>
#include "abonnement.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:






    void on_ajouter_clicked();

    void on_pb_supprimer_2_clicked();

    void on_Modifier_clicked();

private:
    Ui::MainWindow *ui;
abonnement Etmp;
};
#endif // MAINWINDOW_H
