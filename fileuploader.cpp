#include "fileuploader.h"

fileUploader::fileUploader(QString filePath, QUrl url, QObject *parent) : QObject(parent)
{
    QHttpMultiPart* multipart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    
    QHttpPart uploaderPart;
    uploaderPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"uploaderId\""));
    //uploaderPart.setBody(UserObjectId);
    
    QFile* file = new QFile(filePath);
    file->open(QIODevice::ReadOnly);
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\""));
    filePart.setBodyDevice(file);
    
    file->setParent(multipart);
    
    multipart->append(uploaderPart);
    multipart->append(filePart);
    
    QNetworkRequest request(QUrl(SERVER_FILE));
    _networkManager.post(request, multipart);
}

fileUploader::~fileUploader() {}

void fileUploader::fileUploaded(QNetworkReply *_reply)
{

}
