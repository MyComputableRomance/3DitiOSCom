#ifndef FILEUPLOADER_H
#define FILEUPLOADER_H

#include <QObject>
#include "constant.h"
#include <QFile>
#include <QHttpMultiPart>
#include <QHttpPart>

class fileUploader : public QObject
{
    Q_OBJECT
public:
    explicit fileUploader(QString filePath, QUrl url, QObject *parent = 0);
    virtual ~fileUploader();

signals:
    void uploaded();

public slots:
    void fileUploaded(QNetworkReply* _reply);

private:
    QNetworkAccessManager _networkManager;
    QString filePath;
};

#endif // FILEUPLOADER_H
