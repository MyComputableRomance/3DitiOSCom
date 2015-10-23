#include "filedownloader.h"

FileDownloader::FileDownloader(QUrl url, QObject *parent) : QObject(parent)
{
    connect(&_networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(fileDownloaded(QNetworkReply*)));
    QNetworkRequest request(url);
    _networkManager.get(request);
}

FileDownloader::~FileDownloader() {}

void FileDownloader::fileDownloaded(QNetworkReply *reply)
{
    _downloadedData = reply->readAll();
    reply->deleteLater();
    emit downloaded();
}

QByteArray FileDownloader::downloadedData() const
{
    return _downloadedData;
}
