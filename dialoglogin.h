#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>

#include "constant.h"

namespace Ui {
class DialogLogin;
}

class DialogLogin : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLogin(QWidget *parent = 0);
    ~DialogLogin();

private slots:
    void replyFinished(QNetworkReply* reply);

    void on_btnCancel_clicked();

    void on_btnLogin_clicked();

private:
    Ui::DialogLogin *ui;

    QNetworkAccessManager *networkAccessManager;
    QNetworkReply *networkReply;
    QNetworkRequest networkRequest;
};

#endif // DIALOGLOGIN_H
