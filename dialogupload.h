#ifndef DIALOGUPLOAD_H
#define DIALOGUPLOAD_H

#include <QDialog>
#include "constant.h"

#include <QHttpMultiPart>
#include <QHttpPart>
#include <QFile>

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

private:
    Ui::DialogUpload *ui;

    QNetworkReply* _reply;
};

#endif // DIALOGUPLOAD_H
