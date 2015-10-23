#ifndef DIALOGDOWNLOAD_H
#define DIALOGDOWNLOAD_H

#include <QDialog>
#include "constant.h"
#include "filedownloader.h"
#include <QFile>
#include <QFileInfo>

namespace Ui {
class DialogDownload;
}

class DialogDownload : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDownload(QWidget *parent = 0);
    ~DialogDownload();

private slots:
    void on_btnDownload_clicked();

    void saveFile();

    void on_newFile_clicked();

private:
    Ui::DialogDownload *ui;
    FileDownloader* fd;
};

#endif // DIALOGDOWNLOAD_H
