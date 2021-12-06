#include "mailing.h"

#include <QDesktopServices>

#include <QUrl>
void MainWindow::on_mailing_clicked()
{
    QString link="https://mail.google.com/mail/u/0/#inbox?compose=new";
    QDesktopServices::openUrl(link);
}
