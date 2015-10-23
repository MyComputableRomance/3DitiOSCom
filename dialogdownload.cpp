#include "dialogdownload.h"
#include "ui_dialogdownload.h"

DialogDownload::DialogDownload(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDownload)
{
    ui->setupUi(this);
}

DialogDownload::~DialogDownload()
{
    delete ui;
}

void DialogDownload::on_btnDownload_clicked()
{
    QUrl url(QString(ui->lineEdit->text()));
    fd = new FileDownloader(url, this);
    connect(fd, SIGNAL(downloaded()), this, SLOT(saveFile()));
}

void DialogDownload::saveFile()
{
    QFile* file = new QFile(QString("/Users/Tyler/Desktop/test.png"));
    file->open(QIODevice::WriteOnly);
    file->write(fd->downloadedData());
    file->close();
    ui->textBrowser->append(fd->downloadedData());
}

void DialogDownload::on_newFile_clicked()
{
    QFile* file = new QFile("/Users/Tyler/Desktop/tes.dat");
    file->open(QIODevice::ReadWrite);
    file->close();
}
