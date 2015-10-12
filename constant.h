#ifndef CONSTANT
#define CONSTANT

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

#define SERVER_IP "http://202.120.40.90:13337"
#define SERVER_USER "http://202.120.40.90:13337/user"
#define SERVER_FILE "http://202.120.40.90:13337/file"
#define SERVER_FRIEND "http://202.120.40.90:13337/user/"

#define LCAPPID "jwuoc0zLQtI8BzI4Gyfw3wge"
#define LCAPPKEY "8rp1BcK18mJR3yRk5qlCsNk5"
#define LCAPPMASTERKEY "j2LDRNHhgiDhNU5ICBjx5mrL,master"

#define LCSERVER "https://api.leancloud.cn/1.1/"
#define LCSERVER_USER "https://api.leancloud.cn/1.1/users"
#define LCSERVER_LOGIN "https://api.leancloud.cn/1.1/login"
#define LCSERVER_CONVERSATION "https://api.leancloud.cn/1.1/classes/_Conversation"
#define LCSERVER_MSG "https://leancloud.cn/1.1/rtm/messages"
#define LCSERVER_MSG_LOG "https://leancloud.cn/1.1/rtm/messages/logs"

extern QString Username;
extern QString UserObjectId;
extern QString SessionToken;
extern QString LCObjectId;
extern QString LCSessionToken;
extern QString LCUsername;
//extern QString LCConversationId;
//extern QString SelectedFriendName;

#endif // CONSTANT

