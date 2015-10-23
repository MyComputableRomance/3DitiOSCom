#include "dialogaddfriends.h"
#include "ui_dialogaddfriends.h"

DialogAddFriends::DialogAddFriends(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddFriends)
{
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
    QString keyString = ui->lineFriendsUsername->text();
    addFriendByKey(keyString);
    /*QByteArray postData;

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
    _reply = _addFriendManager->post(_request,postData);*/

}

void DialogAddFriends::addFriendByKey(QString _keyString)
{
    QNetworkAccessManager* _manager = new QNetworkAccessManager();

    QByteArray postData;
    QJsonObject jsonData;
    jsonData.insert("type", "addFriend");
    jsonData.insert("keyString", _keyString);
    QJsonDocument jdoc;
    jdoc.setObject(jsonData);
    postData = jdoc.toJson(QJsonDocument::Compact);

    QUrl addFriendUrl(QString(SERVER_FRIEND+UserObjectId));
    QNetworkRequest addRequest;
    addRequest.setUrl(addFriendUrl);
    addRequest.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    connect(_manager,SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    _reply = _manager->post(addRequest, postData);
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

