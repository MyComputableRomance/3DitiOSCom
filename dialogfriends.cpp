#include "dialogfriends.h"
#include "ui_dialogfriends.h"

DialogFriends::DialogFriends(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFriends)
{
    _networkManager = new QNetworkAccessManager();
    ui->setupUi(this);
    getFriendList();
    lastestTimestamp = 0;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerRcv()));
    timer->start(500);

    //ui->browserContext->append("WEQWEQWE");
}

DialogFriends::~DialogFriends()
{
    delete ui;
    delete timer;
}

void DialogFriends::timerRcv()
{
    //ui->browserContext->append("12312");
    if(selectedFriendName != "")
        rcvCon(10, true);
}

void DialogFriends::getFriendList()
{
    QUrl url(QString(SERVER_FRIEND + UserObjectId));
    _request.setUrl(url);

    connect(_networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    _reply = _networkManager->get(_request);
}

void DialogFriends::replyFinished(QNetworkReply *reply)
{
    QByteArray result = reply->readAll();
    //ui->browserContext->setText(QString(result));
    if(reply->error() == QNetworkReply::NoError)
    {
        QJsonParseError jsonParse;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(result, &jsonParse);
        if(jsonParse.error == QJsonParseError::NoError)
        {
            if(jsonDoc.isObject())
            {
                QJsonObject userJson = jsonDoc.object();
                if(userJson.contains("friends"))
                {
                    QJsonValue friendsValue = userJson.take("friends");
                    if(friendsValue.isArray())
                    {
                        QJsonArray friendsArray = friendsValue.toArray();
                        for(int i = 0;i < friendsArray.size();i ++)
                        {
                            QJsonValue friendsArrayValue = friendsArray.at(i);
                            if(friendsArrayValue.isObject())
                            {
                                QJsonObject friendsObject = friendsArrayValue.toObject();
                                if(friendsObject.contains("username"))
                                {

                                    QJsonValue friendsObjectUsername = friendsObject.take("username");
                                    listFriendName.append(friendsObjectUsername.toString());
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    createFriendList();
    reply->deleteLater();
}

void DialogFriends::createFriendList()
{
    ui->browserContext->append("1");
    ui->listFriends->addItems(listFriendName);
    connect(ui->listFriends, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(listItemClicked(QListWidgetItem*)));
}

void DialogFriends::setConversationId(QString friendName)
{
    if(friendName == "")
        return;

    QNetworkAccessManager* cvsManager = new QNetworkAccessManager();
    QNetworkRequest cvsRequest;

    QUrl cvsUrl(QString(LCSERVER_CONVERSATION));

    cvsRequest.setUrl(cvsUrl);

    cvsRequest.setRawHeader("Content-Type", "application/json");
    cvsRequest.setRawHeader("X-LC-Id", LCAPPID);
    cvsRequest.setRawHeader("X-LC-Key", LCAPPKEY);

    connect(cvsManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(cvsReplyFinished(QNetworkReply*)));
    _reply = cvsManager->get(cvsRequest);
}

void DialogFriends::listItemClicked(QListWidgetItem *item)
{
    QString friendName = item->text();
    selectedFriendName = friendName;
    ui->browserContext->append(selectedFriendName);
    setConversationId(selectedFriendName);

    //ui->browserContext->clear();
}

void DialogFriends::cvsReplyFinished(QNetworkReply *reply)
{
    QByteArray result = reply->readAll();
    //ui->browserContext->append(QString(result));
    if(reply->error() == QNetworkReply::NoError)
    {
        QJsonParseError jsonParse;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(result, &jsonParse);
        if(jsonParse.error == QJsonParseError::NoError)
        {
            if(jsonDoc.isObject())
            {
                QJsonObject resultObject = jsonDoc.object();
                if(resultObject.contains("results"))
                {
                    QJsonValue conversationValue = resultObject.take("results");
                    if(conversationValue.isArray())
                    {
                        QJsonArray cvsArray = conversationValue.toArray();
                        for(int i = 0;i < cvsArray.size();i ++)
                        {
                            QJsonValue cvsObV = cvsArray.at(i);
                            if(cvsObV.isObject())
                            {
                                QJsonObject cvsOb = cvsObV.toObject();
                                if(cvsOb.contains("name") && cvsOb.contains("friendName"))
                                {
                                    QString cvsName = cvsOb.take("name").toString();
                                    QString cvsFriendName = cvsOb.take("friendName").toString();
                                    //ui->browserContext->append(cvsFriendName);
                                    if(cvsName == Username && cvsFriendName == selectedFriendName || cvsName == selectedFriendName && cvsFriendName == Username)
                                    {
                                        conversationId = cvsOb.take("objectId").toString();
                                        ui->browserContext->append(conversationId);

                                        rcvCon(10, false);
                                        reply->deleteLater();
                                        return;
                                    }
                                }
                            }
                        }
                        callCreateConversation();
                    }
                }
            }
        }
        reply->deleteLater();
    }
}

void DialogFriends::callCreateConversation()
{
    QNetworkAccessManager* cvsCreateManager = new QNetworkAccessManager();
    QNetworkRequest cvsCreateRequest;

    QUrl cvsCreateUrl(QString(LCSERVER_CONVERSATION));
    QJsonObject cvsJson;
    cvsJson.insert("name", Username);
    cvsJson.insert("friendName", selectedFriendName);
    cvsJson.insert("m", "[\"" + selectedFriendName +"\", \"" + Username + "\"]");
    QJsonDocument jsonDoc;
    jsonDoc.setObject(cvsJson);
    QByteArray postData = jsonDoc.toJson(QJsonDocument::Compact);

    cvsCreateRequest.setUrl(cvsCreateUrl);
    cvsCreateRequest.setRawHeader("Content-Type", "application/json");
    cvsCreateRequest.setRawHeader("X-LC-Id", LCAPPID);
    cvsCreateRequest.setRawHeader("X-LC-Key", LCAPPKEY);

    connect(cvsCreateManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(cvsCreateReplyFinished(QNetworkReply*)));
    _reply = cvsCreateManager->post(cvsCreateRequest, postData);
}

void DialogFriends::cvsCreateReplyFinished(QNetworkReply *reply)
{
    QByteArray result = reply->readAll();
    ui->browserContext->append(QString(result));

    QJsonParseError jsonParse;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(result, &jsonParse);
    if(jsonParse.error == QJsonParseError::NoError)
    {
        if(jsonDoc.isObject())
        {
            QJsonObject cvsJson = jsonDoc.object();
            if(cvsJson.contains("objectId"))
            {
                conversationId = cvsJson.take("objectId").toString();
                ui->browserContext->append(conversationId);
            }
        }
    }
    reply->deleteLater();
}

void DialogFriends::on_btnAddFriend_clicked()
{
    DialogAddFriends* daf = new DialogAddFriends(this);
    daf->show();
}

void DialogFriends::on_btnBack_clicked()
{
    this->close();
}

void DialogFriends::on_btnEmotion_clicked()
{
    getFriendList();
    createFriendList();
}

void DialogFriends::on_btnSend_clicked()
{
    QNetworkAccessManager* msgManager = new QNetworkAccessManager();
    QNetworkRequest msgRequest;

    QString msg = ui->msgEditor->toPlainText();
    ui->msgEditor->clear();
    //ui->browserContext->append(Username + " " + QDateTime::currentDateTime().toString());
    //ui->browserContext->append(msg);

    QUrl msgUrl(QString(LCSERVER_MSG));
    msgRequest.setUrl(msgUrl);
    msgRequest.setRawHeader("Content-Type", "application/json");
    msgRequest.setRawHeader("X-LC-Id", LCAPPID);
    msgRequest.setRawHeader("X-LC-Key", LCAPPMASTERKEY);

    QJsonObject msgJson;
    msgJson.insert("from_peer", UserObjectId);
    msgJson.insert("message", msg);
    msgJson.insert("conv_id", conversationId);
    msgJson.insert("transient", false);
    QJsonDocument msgJsonDoc;
    msgJsonDoc.setObject(msgJson);
    QByteArray msgData = msgJsonDoc.toJson(QJsonDocument::Compact);

    connect(msgManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(msgReplyFinished(QNetworkReply*)));
    _reply = msgManager->post(msgRequest, msgData);
}

void DialogFriends::msgReplyFinished(QNetworkReply * reply)
{
    QByteArray result = reply->readAll();
    //ui->browserContext->append(QString(result));
    reply->deleteLater();
}

void DialogFriends::on_btnTest_clicked()
{

}

void DialogFriends::rcvCon(int _num, bool _check)
{
    if(_num < 0 || _num > 1000)
        _num = 10;

    //ui->browserContext->append("2");
    QNetworkAccessManager* _rcvManager = new QNetworkAccessManager();
    QNetworkRequest _rcvRequest;

    QUrl msgLog(QString(LCSERVER_MSG_LOG));
    QUrlQuery params;
    params.addQueryItem("convid", conversationId);
    params.addQueryItem("limit", QString::number(_num));
    msgLog.setQuery(params);

    _rcvRequest.setUrl(msgLog);
    _rcvRequest.setRawHeader("Content-Type", "application/json");
    _rcvRequest.setRawHeader("X-LC-Id", LCAPPID);
    _rcvRequest.setRawHeader("X-LC-Key", LCAPPMASTERKEY);

    if(!_check)
        connect(_rcvManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(msgLogFinished(QNetworkReply*)));
    else
        connect(_rcvManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(msgLogCheckedFinished(QNetworkReply*)));

    _reply = _rcvManager->get(_rcvRequest);
}


//used in the beginning of initiation without checking timestamp
void DialogFriends::msgLogFinished(QNetworkReply * reply)
{
    //ui->browserContext->append("3");
    //ui->browserContext->append(reply->readAll());
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray result = reply->readAll();
        ui->browserContext->append(result);
        QJsonParseError jsonParse;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(result, &jsonParse);
        if(jsonParse.error == QJsonParseError::NoError)
        {
            if(jsonDoc.isArray())
            {
                QJsonArray msgArray = jsonDoc.array();
                for(int i = msgArray.size() - 1;i >= 0;i --)
                {
                    QJsonValue msgValue = msgArray.at(i);
                    if(msgValue.isObject())
                    {
                        QJsonObject msgObject = msgValue.toObject();
                        if(msgObject.contains("timestamp"))
                        {
                            QJsonValue tsValue = msgObject.take("timestamp");
                            long long ts = (long long)tsValue.toDouble();
                            QDateTime dt;
                            dt.setTime_t(ts / 1000);
                            if(ts >= lastestTimestamp)
                                lastestTimestamp = ts;

                            if(msgObject.contains("from"))
                            {
                                QString senderName = "";
                                QString senderId = msgObject.take("from").toString();
                                if(senderId != UserObjectId)
                                    senderName = selectedFriendName;
                                else
                                    senderName = Username;

                                if(msgObject.contains("data"))
                                {
                                    QString msg;
                                    QJsonValue dataValue = msgObject.take("data");
                                    if(dataValue.isString())
                                    {
                                        msg = dataValue.toString();
                                    }
                                    else if(dataValue.isObject())
                                    {

                                    }
                                    ui->browserContext->append(senderName + " " + dt.toString());
                                    ui->browserContext->append(msg);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    reply->deleteLater();
}

//used during realtime chat by checking timestamp
void DialogFriends::msgLogCheckedFinished(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray result = reply->readAll();
        //ui->browserContext->append(result);
        QJsonParseError jsonParse;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(result, &jsonParse);
        if(jsonParse.error == QJsonParseError::NoError)
        {
            if(jsonDoc.isArray())
            {
                QJsonArray msgArray = jsonDoc.array();
                for(int i = msgArray.size() - 1;i >= 0;i --)
                {
                    QJsonValue msgValue = msgArray.at(i);
                    if(msgValue.isObject())
                    {
                        QJsonObject msgObject = msgValue.toObject();
                        if(msgObject.contains("timestamp"))
                        {
                            QJsonValue tsValue = msgObject.take("timestamp");
                            long long ts = (long long)tsValue.toDouble();
                            QDateTime dt;
                            dt.setTime_t(ts / 1000);

                            if(ts > lastestTimestamp)
                            {
                                lastestTimestamp = ts;
                            }
                            else
                            {
                                continue;
                            }

                            if(msgObject.contains("from"))
                            {
                                QString senderName = "";
                                QString senderId = msgObject.take("from").toString();
                                if(senderId != UserObjectId)
                                    senderName = selectedFriendName;
                                else
                                    senderName = Username;

                                if(msgObject.contains("data"))
                                {
                                    QString msg;
                                    QJsonValue dataValue = msgObject.take("data");
                                    if(dataValue.isString())
                                    {
                                        msg = dataValue.toString();
                                    }
                                    else if(dataValue.isObject())
                                    {

                                    }
                                    ui->browserContext->append(senderName + " " + dt.toString());
                                    ui->browserContext->append(msg);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    reply->deleteLater();
}


void DialogFriends::on_btnlastmsg_clicked()
{
    int fn = listFriendName.size();
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(lastMsgFinished(QNetworkReply*)));
    QNetworkRequest request;
    for(int i = 0;i < fn;i ++)
    {
        setConversationId(listFriendName.at(i));

        QUrl msgLog(QString(LCSERVER_MSG_LOG));
        QUrlQuery params;
        params.addQueryItem("convid", conversationId);
        params.addQueryItem("limit", QString::number(1));
        msgLog.setQuery(params);

        request.setUrl(msgLog);
        request.setRawHeader("X-LC-Id", LCAPPID);
        request.setRawHeader("X-LC-Key", LCAPPKEY);

        _reply = manager->get(request);
    }
}

void DialogFriends::lastMsgFinished(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray result = reply->readAll();
        QJsonParseError jsonParse;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(result, &jsonParse);
        if(jsonParse.error == QJsonParseError::NoError)
        {
            if(jsonDoc.isArray())
            {
                QJsonObject lastMsg;
                QJsonArray msgArray = jsonDoc.array();
                if(msgArray.size() <= 0)
                {
                    lastMsg.insert("data", "");
                    lastMsg.insert("timestamp", "");
                }
                else
                {
                    QJsonValue msgValue = jsonDoc.array().at(0);
                    lastMsg.insert("data", msgValue.toObject().take("data"));
                    lastMsg.insert("timestamp", msgValue.toObject().take("timestamp"));
                }

                lastMsgList.push_back(lastMsg);
            }
        }
    }
    reply->deleteLater();
}
