#include "timersetter.h"

TimerSetter::TimerSetter(QWidget *parent)
    : QLabel(parent)
{

}

void TimerSetter::mouseDoubleClickEvent(QMouseEvent *event)
{
    SetTimeDialog *dlgSetTime = new SetTimeDialog(this);
    int ret = dlgSetTime->exec();
    if (ret == QDialog::Accepted)
    {
        QString dt = dlgSetTime->getDateTime();
        QString cmd = QString("date -s '%1' && hwclock -w").arg(dt);
        system(cmd.toStdString().c_str());
        setText(dt);
    }
    delete dlgSetTime;
}
