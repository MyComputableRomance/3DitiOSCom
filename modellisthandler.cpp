#include "modellisthandler.h"

ModelListHandler::ModelListHandler(QObject *parent) : QObject(parent)
{
    connect(&_modelListManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getModelListReplyFinished(QNetworkReply*)));
}

ModelListHandler::~ModelListHandler() {}

void ModelListHandler::execute()
{
    QUrl url(QString(SERVER_FILE));
    QUrlQuery params;
    params.addQueryItem("uploaderId", UserObjectId);
    url.setQuery(params);

    QNetworkRequest request(url);
    _modelListManager.get(request);
}

void ModelListHandler::getModelListReplyFinished(QNetworkReply *reply)
{
    /* QStringList Model Sequence
     * uploaderId
     * fileName
     * filePath
     * fileSize
     * fileDescriptor
     * fileIconPath
     * fileThumbnailPathArray {6}
     * */

    if(reply->error() == QNetworkReply::NoError)
    {
        QByteArray result = reply->readAll();
        QJsonParseError jsonParse;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(result, &jsonParse);
        if(jsonDoc.isArray())
        {
            QJsonArray allModelList = jsonDoc.array();
            for(int i = 0;i < allModelList.size();i ++)
            {
                QStringList modelSpecs;
                QJsonObject modelObject = allModelList.at(i).toObject();
                modelSpecs.append(UserObjectId);
                if(modelObject.contains("fileName")) modelSpecs.append(modelObject.take("fileName").toString());
                if(modelObject.contains("filePath")) modelSpecs.append(modelObject.take("fileSize").toString());
                if(modelObject.contains("fileDescriptor")) modelSpecs.append(modelObject.take("fileDescriptor").toString());
                if(modelObject.contains("fileIconPath")) modelSpecs.append(modelObject.take("fileIconPath").toString());

                _modelList.append(modelSpecs);
            }
        }
    }
    reply->deleteLater();
}

