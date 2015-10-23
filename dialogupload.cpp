#include "dialogupload.h"
#include "ui_dialogupload.h"

DialogUpload::DialogUpload(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUpload)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
    path = QString(SERVER_IP)+QString("/stl/3ed67567-920c-4cb4-bdc0-bec89c646e67.stl");
}

DialogUpload::~DialogUpload()
{
    delete ui;
}

void DialogUpload::on_btnUploadFile_clicked()
{
    QHttpMultiPart* multipart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    //QJsonObject uploaderJson;
    //uploaderJson.insert("uploaderId", UserObjectId);
    //QJsonDocument uploaderDoc;
    //uploaderDoc.setObject(uploaderJson);

    QHttpPart uploaderPart;
    //uploaderPart.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    uploaderPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data;name=\"uploaderId\""));
    uploaderPart.setBody(UserObjectId.toLatin1());

    QFile* file = new QFile("/Users/Tyler/Pictures/test.jpg");
    file->open(QIODevice::ReadOnly);

    QHttpPart filePart;
    //filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant());
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name = \"file\""));
    filePart.setBodyDevice(file);

    file->setParent(multipart);

    multipart->append(uploaderPart);
    multipart->append(filePart);

    QUrl fileUrl(SERVER_FILE);
    QNetworkRequest request(fileUrl);

    QNetworkAccessManager* _fileManager = new QNetworkAccessManager(this);
    connect(_fileManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    //connect(_fileReply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));
    _fileReply = _fileManager->post(request, multipart);
}

void DialogUpload::replyFinished(QNetworkReply *reply)
{
    QByteArray result = reply->readAll();
    ui->console->setText(result);
    reply->deleteLater();
}

void DialogUpload::on_btnDownload_clicked()
{
    QUrl url(path);
    QFileInfo fileInfo(url.path());
    QString filename = fileInfo.fileName();
    if(filename.isEmpty())
        filename = "test.dat";

    file = new QFile(filename);
    file->open(QIODevice::WriteOnly);

    QNetworkRequest downloadRequest;
    downloadRequest.setUrl(url);

    QNetworkAccessManager* _downloadManager = new QNetworkAccessManager(this);
    connect(_downloadManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));
    connect(_reply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));
    connect(_reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(QdownloadProgress(qint64,qint64)));
    _reply = _downloadManager->get(downloadRequest);
}

void DialogUpload::downloadFinished(QNetworkReply *reply)
{
    //ui->console->setText(reply->readAll());
    //QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if(reply->error() == QNetworkReply::NoError)
    {
        if(file->exists())
            ui->console->setText(QString::number(file->size()));
        else
            ui->console->setText("f");
        //file->write(reply->readAll());
        //file->remove();
        //ui->set
    }
    reply->deleteLater();
    //delete file;
}

void DialogUpload::httpReadyRead()
{
    file->write(_reply->readAll());
    //file->close();
}

void DialogUpload::QdownloadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    ui->progressBar->setMaximum(bytesTotal);
    ui->progressBar->setValue(bytesSent);
}

void DialogUpload::on_btnCancelDownload_clicked()
{

}
