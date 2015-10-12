#include "dialogaddfriends.h"
#include "ui_dialogaddfriends.h"

DialogAddFriends::DialogAddFriends(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddFriends)
{
    _addFriendManager = new QNetworkAccessManager();
    ui->setupUi(this);
}

DialogAddFriends::~DialogAddFriends()
{
    delete ui;
}

void DialogAddFriends::on_Ok_clicked()
{
    this->close();
}

void DialogAddFriends::on_btnAddFriend_clicked()
{
    QString friendName = ui->lineFriendsUsername->text();
    QByteArray postData;

    QJsonObject addFriendJson;
    addFriendJson.insert("type", "addFriend");
    addFriendJson.insert("friendName", friendName);
    QJsonDocument jdoc;
    jdoc.setObject(addFriendJson);
    postData = jdoc.toJson(QJsonDocument::Compact);


    QUrl addFriendUrl(QString(SERVER_FRIEND+UserObjectId));
    _request.setUrl(addFriendUrl);
    _request.setRawHeader("Content-Type", "application/json");
    connect(_addFriendManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    _reply = _addFriendManager->post(_request,postData);

}

void DialogAddFriends::replyFinished(QNetworkReply *networkReply)
{
    QVariant status = networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    QByteArray info;
    info = networkReply->readAll();
    ui->labelConsole->setText(QString(info));
    if(networkReply->error() == QNetworkReply::NoError)
    {

    }
    else
    {

    }
    networkReply->deleteLater();
}

