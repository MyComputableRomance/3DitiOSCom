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

    //void addFriendByEmail(QString);
    void addFriendByKey(QString);
    //void addFriendByPhone(QString);

private slots:
    void on_Ok_clicked();

    void on_btnAddFriend_clicked();

    void replyFinished(QNetworkReply* reply);

private:
    Ui::DialogAddFriends *ui;
    QNetworkReply* _reply;
};

#endif // DIALOGADDFRIENDS_H
