#ifndef DIALOGMODIFY_H
#define DIALOGMODIFY_H

#include <QDialog>
#include "modifyprofilehandler.h"

namespace Ui {
class DialogModify;
}

class DialogModify : public QDialog
{
    Q_OBJECT

public:
    explicit DialogModify(QWidget *parent = 0);
    ~DialogModify();

private slots:
    void on_pushButton_clicked();
    void modifiedFinished();

private:
    Ui::DialogModify *ui;
    ModifyProfileHandler mp;
};

#endif // DIALOGMODIFY_H
