#include "dialogregister.h"
#include "ui_dialogregister.h"

DialogRegister::DialogRegister(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRegister)
{
    ui->setupUi(this);
}

DialogRegister::~DialogRegister()
{
    delete ui;
}

bool DialogRegister::checkUsername()
{
    QString usernamePattern("[A-Za-z0-9_]{6,30}");
    QRegExp usernameRegExp(usernamePattern);
    return usernameRegExp.exactMatch(ui->lineUsername->text());
}

bool DialogRegister::checkPassword()
{
    QString passwordPattern("[A-Za-z0-9_@]{6,15}");
    QRegExp passwordRegExp(passwordPattern);
    return passwordRegExp.exactMatch(ui->linePassword->text());
}

bool DialogRegister::checkConfirmPassword()
{
    if(ui->linePassword->text() == ui->lineConfirmPassword->text())
        return true;
    else
        return false;
}

bool DialogRegister::checkEmail()
{
    QString emailPattern("^[a-z0-9]+([._\\-]*[a-z0-9])*@([a-z0-9]+[-a-z0-9]*[a-z0-9]+.){1,63}[a-z0-9]+$");
    QRegExp emailRegExp(emailPattern);
    return emailRegExp.exactMatch(ui->lineEmail->text());
}

bool DialogRegister::checkPhone()
{
    QString phonePattern("[0-9]{6,13}");
    QRegExp phoneRegExp(phonePattern);
    return phoneRegExp.exactMatch(ui->linePhone->text());
}

bool DialogRegister::checkMachineID()
{
    return true;
}

void DialogRegister::on_btnOk_clicked()
{
    ui->labelCheckUsername->clear();
    ui->labelCheckPassword->clear();
    ui->labelCheckConfirmPassword->clear();
    ui->labelCheckEmail->clear();
    ui->labelCheckPhone->clear();
    ui->labelCheckMachineID->clear();

    if(!checkUsername())
    {
        ui->labelCheckUsername->setText("Invalid Username");
        return;
    }

    if(!checkPassword())
    {
        ui->labelCheckPassword->setText("Invalid Password");
        return;
    }

    if(!checkConfirmPassword())
    {
        ui->labelCheckConfirmPassword->setText("Passwords Don't Match");
        return;
    }

    if(!checkEmail())
    {
        ui->labelCheckEmail->setText("Invalid Email Address");
        return;
    }

    if(!checkMachineID())
    {
        ui->labelCheckMachineID->setText("");
        return;
    }

    if(!checkPhone())
    {
        ui->labelCheckPhone->setText("Invalid Phone");
        return;
    }

    QJsonObject newUser;
    newUser.insert("username", ui->lineUsername->text());
    newUser.insert("password", ui->linePassword->text());
    newUser.insert("email", ui->lineEmail->text());
    newUser.insert("phone", ui->linePhone->text());
    newUser.insert("machine", ui->lineMachineID->text());
    QJsonDocument document;
    document.setObject(newUser);
    QByteArray post_data = document.toJson(QJsonDocument::Compact);

    QUrl serverUrl(SERVER_USER);
    networkAccessManager = new QNetworkAccessManager();
    networkRequest.setUrl(serverUrl);
    networkRequest.setRawHeader("Content-Type", "application/json");
    //
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    networkReply = networkAccessManager->post(networkRequest, post_data);

    //newUser.remove("machine");
    QUrl lcserverUser(LCSERVER_USER);
    networkRequest.setUrl(lcserverUser);
    networkRequest.setRawHeader("X-LC-Id", LCAPPID);
    networkRequest.setRawHeader("X-LC-Key", LCAPPKEY);
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    lcreply = networkAccessManager->post(networkRequest, post_data);

}

void DialogRegister::replyFinished(QNetworkReply *networkReply)
{
    QVariant status = networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(networkReply->error() == QNetworkReply::NoError)
    {

    }
    else
    {

    }
    networkReply->deleteLater();
}


void DialogRegister::on_btnBack_clicked()
{
    ui->labelCheckUsername->clear();
    ui->labelCheckPassword->clear();
    ui->labelCheckConfirmPassword->clear();
    ui->labelCheckEmail->clear();
    ui->labelCheckPhone->clear();
    ui->labelCheckMachineID->clear();

    this->close();
}
