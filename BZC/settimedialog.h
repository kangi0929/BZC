#ifndef SETTIMEDIALOG_H
#define SETTIMEDIALOG_H

#include <QDialog>

namespace Ui {
class SetTimeDialog;
}

class SetTimeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetTimeDialog(QWidget *parent = nullptr);
    ~SetTimeDialog();

public:
    QString getDateTime();

private:
    Ui::SetTimeDialog *ui;
};

#endif // SETTIMEDIALOG_H
