#ifndef MODELLISTHANDLER_H
#define MODELLISTHANDLER_H

#include <QObject>
#include "constant.h"

class ModelListHandler : public QObject
{
    Q_OBJECT
public:
    explicit ModelListHandler(QObject *parent = 0);
    ~ModelListHandler();

    QList<QStringList> getModelList() { return _modelList; };

    void execute();

signals:
    void getModelListFinished();

public slots:
    void getModelListReplyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager _modelListManager;
    QList<QStringList> _modelList;
};

#endif // MODELLISTHANDLER_H
