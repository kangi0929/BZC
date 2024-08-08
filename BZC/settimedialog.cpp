#include "settimedialog.h"
#include "ui_settimedialog.h"

SetTimeDialog::SetTimeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetTimeDialog)
{
    ui->setupUi(this);
    setWindowTitle("设置时间");
    QDateTime dt = QDateTime::currentDateTime();
    ui->dateTimeEdit->setDateTime(dt);
    ui->dateTimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
}

SetTimeDialog::~SetTimeDialog()
{
    delete ui;
}

QString SetTimeDialog::getDateTime()
{
    return ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss");
}
