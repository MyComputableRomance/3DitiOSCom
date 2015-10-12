#ifndef DIALOGREGISTER_H
#define DIALOGREGISTER_H

#include <QDialog>
#include <QRegExp>

#include "constant.h"

namespace Ui {
class DialogRegister;
}

class DialogRegister : public QDialog
{
    Q_OBJECT

public:
    explicit DialogRegister(QWidget *parent = 0);
    ~DialogRegister();

private slots:
    void replyFinished(QNetworkReply* reply);

    void on_btnOk_clicked();

    void on_btnBack_clicked();

private:
    Ui::DialogRegister *ui;

    bool uniqueUsername();
    bool uniqueMachineID();

    bool checkUsername();
    bool checkPassword();
    bool checkConfirmPassword();
    bool checkEmail();
    bool checkPhone();
    bool checkMachineID();

    QNetworkAccessManager *networkAccessManager;
    QNetworkReply *networkReply;
    //QNetworkReply* LCReply;
    QNetworkRequest networkRequest;

    QNetworkRequest lcrequest;
    QNetworkReply* lcreply;
};

#endif // DIALOGREGISTER_H
