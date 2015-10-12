#include "mainwindow.h"
#include "ui_mainwindow.h"

extern QString Username = "";
extern QString UserObjectId = "";
extern QString SessionToken = "";
extern QString LCObjectId = "";
extern QString LCSessionToken = "";
extern QString LCUsername = "";
//extern QString SelectedFriendName = "";
//extern QString LCConversationId = "";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connect_clicked()
{
    QString url = "http://";
    url += ui->url->toPlainText();
    QUrl serverUrl(url);
    QByteArray post_data;
    post_data.append(ui->data->toPlainText());
    networkAccessManager = new QNetworkAccessManager(this);
    //networkRequest = new QNetworkRequest();
    networkRequest.setUrl(serverUrl);
    
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    //networkReply = networkAccessManager->post(networkRequest, post_data);
    networkReply = networkAccessManager->get(networkRequest);
    ui->url->clear();
    ui->data->clear();
}

void MainWindow::replyFinished(QNetworkReply *networkReply)
{
    QVariant status_code = networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    ui->console->clear();

    if(networkReply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = networkReply->readAll();

        QJsonParseError json_error;
        QJsonDocument parse_document = QJsonDocument::fromJson(bytes, &json_error);
        if(json_error.error == QJsonParseError::NoError)
        {
            if(parse_document.isObject())
            {
                ui->console->append("is object");

            }
            if(parse_document.isArray())
            {
                ui->console->append("is array");
            }
        }

        QString result(bytes);

        ui->console->append(result);
    }
    else
    {
        ui->console->append("Failed");
    }
    networkReply->deleteLater();
}

void MainWindow::on_btnRegister_clicked()
{
    ui->console->setText("Register");
    //QMessageBox::warning(NULL, "Alert", "Hello", QMessageBox::Yes, QMessageBox::Yes);
    DialogRegister* dr = new DialogRegister(this);
    dr->show();
}

void MainWindow::on_btnLogin_clicked()
{
    DialogLogin* dl = new DialogLogin(this);
    dl->show();
}


void MainWindow::on_btnInfo_clicked()
{
    ui->console->append("Info");
    ui->console->append(Username);
    ui->console->append(UserObjectId);
    ui->console->append(SessionToken);
    ui->console->append(LCUsername);
    ui->console->append(LCObjectId);
    ui->console->append(LCSessionToken);
}

void MainWindow::on_btnFriend_clicked()
{
    DialogFriends* df = new DialogFriends(this);
    df->show();
}

void MainWindow::on_btnUpload_clicked()
{
    DialogUpload* du = new DialogUpload(this);
    du->show();
}
