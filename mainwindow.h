#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "constant.h"
#include <QMainWindow>
#include <QMessageBox>

#include "dialogregister.h"
#include "dialoglogin.h"
#include "dialogfriends.h"
#include "dialogdownload.h"
#include "dialogmodify.h"
#include "modellisthandler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_connect_clicked();

    void replyFinished(QNetworkReply* reply);


    void on_btnRegister_clicked();

    void on_btnLogin_clicked();

    void on_btnInfo_clicked();

    //void on_btnUpload_clicked();
    
    void on_btnFriend_clicked();

    void on_btnUpload_clicked();

    void on_btnDownload_clicked();

    void on_btnSync_clicked();

    void on_btnPrint_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkAccessManager;
    QNetworkReply *networkReply;
    QNetworkRequest networkRequest;
    ModelListHandler mlh;

};

#endif // MAINWINDOW_H
