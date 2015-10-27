#ifndef MODIFYPROFILEHANDLER_H
#define MODIFYPROFILEHANDLER_H

#include <QObject>
#include "constant.h"

class ModifyProfileHandler : public QObject
{
    Q_OBJECT
public:
    explicit ModifyProfileHandler(QObject *parent = 0);
    ~ModifyProfileHandler();

    //QString modifiedProfile() const;
    //void setChangedUsername(QString un) { _changedUsername = un; };
    void setChangedEmail(QString em) { _changedEmail = em; };
    bool executeResult() { return _resultCode; };
    void execute();

signals:

    void modified();

public slots:

    void modifiedReplyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager _modifyProfileManager;
    //QString _modifiedProfileInfo;
    //QString _changedUsername;
    QString _changedEmail;
    bool _resultCode;
};

#endif // MODIFYPROFILEHANDLER_H
