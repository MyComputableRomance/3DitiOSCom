#ifndef DIALOGUPLOAD_H
#define DIALOGUPLOAD_H

#include <QDialog>
#include "constant.h"

#include <QHttpMultiPart>
#include <QHttpPart>
#include <QFile>
#include <QFileInfo>

namespace Ui {
class DialogUpload;
}

class DialogUpload : public QDialog
{
    Q_OBJECT

public:
    explicit DialogUpload(QWidget *parent = 0);
    ~DialogUpload();

private slots:
    void on_btnUploadFile_clicked();

    void replyFinished(QNetworkReply*);

    void on_btnDownload_clicked();

    void on_btnCancelDownload_clicked();

    void downloadFinished(QNetworkReply*);

    void httpReadyRead();

    void QdownloadProgress(qint64 bytesSent, qint64 bytesTotal);

private:
    Ui::DialogUpload *ui;

    QNetworkReply* _reply;
    QNetworkReply* _fileReply;
    QString path;

    QFile* file;
};

#endif // DIALOGUPLOAD_H
