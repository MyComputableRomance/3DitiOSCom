#include "modifyprofilehandler.h"

ModifyProfileHandler::ModifyProfileHandler(QObject *parent) : QObject(parent)
{
    _changedEmail = "";
    //_changedUsername = "";
    connect(&_modifyProfileManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(modifiedReplyFinished(QNetworkReply*)));
}

ModifyProfileHandler::~ModifyProfileHandler() {}

void ModifyProfileHandler::execute()
{
    QUrl url(QString(SERVER_FRIEND) + UserObjectId);

    QJsonObject modifyJson;
    //if(_changedUsername == "")
    //{
    modifyJson.insert("type", "modifyEmail");
    modifyJson.insert("email", _changedEmail);
    //}
    /*else if(_changedEmail == "")
    {
        modifyJson.insert("type", "modifyUsername");
        modifyJson.insert("username", _changedUsername);
    }*/
    QJsonDocument jsonDoc;
    jsonDoc.setObject(modifyJson);
    QByteArray postData = jsonDoc.toJson();

    QNetworkRequest request(url);
    _modifyProfileManager.put(request, postData);
}

void ModifyProfileHandler::modifiedReplyFinished(QNetworkReply *reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray result = reply->readAll();
        QJsonParseError jsonParse;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(result, &jsonParse);
        if(jsonParse.error == QJsonParseError::NoError)
        {
            if(jsonDoc.isObject())
            {
                QJsonObject modifyResultObject = jsonDoc.object();
                if(modifyResultObject.contains("result"))
                {
                    QJsonValue resultCode = modifyResultObject.take("result");
                    //success OK failure ***Error
                    if(resultCode.isString())
                    {
                        if(resultCode.toString() == "OK")
                            _resultCode = true;
                        else
                            _resultCode = false;
                    }
                }
            }
        }
    }
    reply->deleteLater();
    emit modified();
}

/*QString ModifyProfileHandler::modifiedProfile() const
{
    return _modifiedProfileInfo;
}*/

