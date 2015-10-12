#ifndef DIALOGADDFRIENDS_H
#define DIALOGADDFRIENDS_H

#include "constant.h"
#include <QDialog>

namespace Ui {
class DialogAddFriends;
}

class DialogAddFriends : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddFriends(QWidget *parent = 0);
    ~DialogAddFriends();

private slots:
    void on_Ok_clicked();

    void on_btnAddFriend_clicked();

    void replyFinished(QNetworkReply* reply);

private:
    Ui::DialogAddFriends *ui;
    QNetworkAccessManager* _addFriendManager;
    QNetworkReply* _reply;
    QNetworkRequest _request;
};

#endif // DIALOGADDFRIENDS_H
