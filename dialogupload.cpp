#include "dialogupload.h"
#include "ui_dialogupload.h"

DialogUpload::DialogUpload(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUpload)
{
    ui->setupUi(this);
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
    _reply = _fileManager->post(request, multipart);
}

void DialogUpload::replyFinished(QNetworkReply *reply)
{
    QByteArray result = reply->readAll();
    ui->console->setText(result);
    reply->deleteLater();
}
