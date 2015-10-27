#include "dialogmodify.h"
#include "ui_dialogmodify.h"

DialogModify::DialogModify(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogModify)
{
    ui->setupUi(this);
}

DialogModify::~DialogModify()
{
    delete ui;
}

void DialogModify::on_pushButton_clicked()
{
    QString val = ui->lineEdit->text();
    mp.setChangedEmail(val);
    mp.execute();
    connect(&mp, SIGNAL(modified()), this, SLOT(modifiedFinished()));
}

void DialogModify::modifiedFinished()
{
    if(mp.executeResult())
        ui->label->setText(QString("sssss"));
    else
        ui->label->setText(QString("sdsdsdsd"));
}
