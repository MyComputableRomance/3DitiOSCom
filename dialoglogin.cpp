#include "dialoglogin.h"
#include "ui_dialoglogin.h"

DialogLogin::DialogLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogin)
{
    networkAccessManager = new QNetworkAccessManager();
    //networkReply = new QNetworkReply(this);
    ui->setupUi(this);
}

DialogLogin::~DialogLogin()
{
    delete ui;
}

void DialogLogin::on_btnCancel_clicked()
{
    ui->lineUsername->clear();
    ui->linePassword->clear();
    this->close();
}

void DialogLogin::on_btnLogin_clicked()
{
    QString arg("?username="+ui->lineUsername->text()+"&password="+ui->linePassword->text());
    QUrl url(SERVER_USER+arg);
    //ui->labelConsole->setText(SERVER_USER+arg);
    networkRequest.setUrl(url);
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    networkReply = networkAccessManager->get(networkRequest);

    QUrl lcurl = QUrl(LCSERVER_LOGIN);
    //networkRequest.setUrl(lcurl);
    networkRequest.setRawHeader("X-LC-Id", LCAPPID);
    networkRequest.setRawHeader("X-LC-Key", LCAPPKEY);
    QUrlQuery params;
    params.addQueryItem("username", ui->lineUsername->text());
    params.addQueryItem("password", ui->linePassword->text());
    lcurl.setQuery(params);
    networkRequest.setUrl(lcurl);
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    networkReply = networkAccessManager->get(networkRequest);
}

void DialogLogin::replyFinished(QNetworkReply *networkReply)
{
    //QByteArray bytes = networkReply->readAll();
    //ui->labelConsole->setText(QString(bytes));
    if(networkReply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = networkReply->readAll();

        QJsonParseError jsonParse;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(bytes, &jsonParse);
        if(jsonParse.error == QJsonParseError::NoError)
        {
            //LeanCloud
            if(jsonDocument.isObject())
            {
                QJsonObject userJson = jsonDocument.object();
                if(userJson.contains("sessionToken"))
                {
                    QJsonValue sessionTokenValue = userJson.take("sessionToken");
                    LCSessionToken = sessionTokenValue.toString();
                    ui->labelConsole->setText(LCSessionToken);
                }
                if(userJson.contains("objectId"))
                {
                    QJsonValue objectIdValue = userJson.take("objectId");
                    LCObjectId = objectIdValue.toString();
                }
                if(userJson.contains("username"))
                {
                    QJsonValue usernameValue = userJson.take("username");
                    LCUsername = usernameValue.toString();
                }

                networkReply->deleteLater();
                //ui->labelConsole->setText("ss\n");
                return;

                //if(userJson.contains("username") && userJson.contains("password"))
                //{
                //    QJsonValue usernameValue = userJson.take("username");
                //    QJsonValue passwordValue = userJson.take("password");
                //    if(usernameValue.isString() && passwordValue.isString())
                //    {
                //        if(usernameValue.toString() == ui->lineUsername->text() &&
                //           passwordValue.toString() == ui->linePassword->text())
                //        {
                //            currentUser = ui->lineUsername->text();
                //            networkReply->deleteLater();
                //            //ui->labelConsole->setText("Successful");
                //            //QDialog::accept();
                //            //this->close();
                //            return;
                //        }
                //    }
                //}
            }

            //3Dit
            else if(jsonDocument.isArray())
            {
                QJsonValue value = jsonDocument.array().at(0);
                if(value.isObject())
                {
                    QJsonObject userJson = value.toObject();
                    if(userJson.contains("username"))
                    {
                        QJsonValue usernameValue = userJson.take("username");
                        Username = usernameValue.toString();
                    }
                    if(userJson.contains("id"))
                    {
                        QJsonValue objectIdValue = userJson.take("id");
                        UserObjectId = objectIdValue.toString();
                    }
                    if(userJson.contains("sessionToken"))
                    {
                        QJsonValue sessionTokeValue = userJson.take("sessionToken");
                        SessionToken = sessionTokeValue.toString();
                    }

                    networkReply->deleteLater();
                    //ui->labelConsole->setText("s\n");
                    return;

                    //if(userJson.contains("username") && userJson.contains("password"))
                    //{
                    //    QJsonValue usernameValue = userJson.take("username");
                    //    QJsonValue passwordValue = userJson.take("password");
                    //    if(usernameValue.isString() && passwordValue.isString())
                    //    {
                    //        if(usernameValue.toString() == ui->lineUsername->text() &&
                    //           passwordValue.toString() == ui->linePassword->text())
                    //        {
                    //            currentUser = ui->lineUsername->text();
                    //            networkReply->deleteLater();
                    //            //QDialog::accept();
                    //            ui->labelConsole->setText("Successful");
                    //            //this->close();
                    //            return;
                    //        }
                    //    }
                    //}
                }
            }
        }
    }

    ui->lineUsername->clear();
    ui->linePassword->clear();
    //ui->labelConsole->setText("Failed");
    networkReply->deleteLater();
}

