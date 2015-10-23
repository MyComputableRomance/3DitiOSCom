#ifndef FILEDOWNLOADER
#define FILEDOWNLOADER

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class FileDownloader : public QObject
{
    Q_OBJECT

public:
    explicit FileDownloader(QUrl url, QObject* parent = 0);
    virtual ~FileDownloader();

    QByteArray downloadedData() const;

signals:
    void downloaded();

private slots:
    void fileDownloaded(QNetworkReply* reply);

private:
    QNetworkAccessManager _networkManager;
    QByteArray _downloadedData;
};

#endif // FILEDOWNLOADER

