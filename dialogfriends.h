#ifndef DIALOGFRIENDS_H
#define DIALOGFRIENDS_H

#include "constant.h"
#include <QDialog>
#include "dialogaddfriends.h"
#include <QStringList>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTextCodec>
#include <QDateTime>
#include <QStringList>
#include <QTimer>

namespace Ui {
class DialogFriends;
}

class DialogFriends : public QDialog
{
    Q_OBJECT

public:
    explicit DialogFriends(QWidget *parent = 0);
    ~DialogFriends();

    void getFriendList();

    void createFriendList();

    void setConversationId(QString friendName);

    void callCreateConversation();

    void rcvCon(int _num = 100, bool _check = true);

private slots:
    void on_btnAddFriend_clicked();

    void on_btnBack_clicked();

    void replyFinished(QNetworkReply*);

    void on_btnEmotion_clicked();

    void listItemClicked(QListWidgetItem*);

    void cvsReplyFinished(QNetworkReply*);

    void cvsCreateReplyFinished(QNetworkReply*);

    void on_btnSend_clicked();

    void msgReplyFinished(QNetworkReply*);

    void on_btnTest_clicked();

    void msgLogFinished(QNetworkReply*);

    void msgLogCheckedFinished(QNetworkReply*);

    void timerRcv();

private:
    Ui::DialogFriends *ui;

    QNetworkAccessManager* _networkManager;
    QNetworkRequest _request;
    QNetworkReply* _reply;
    QStringList listFriendName;

    QString selectedFriendName;
    QString conversationId;

    long long lastestTimestamp;
    QTimer* timer;
};

#endif // DIALOGFRIENDS_H
