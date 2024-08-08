#ifndef TIMERSETTER_H
#define TIMERSETTER_H

#include <QObject>
#include <QLabel>
#include "settimedialog.h"

class TimerSetter : public QLabel
{
    Q_OBJECT
public:
    TimerSetter(QWidget *parent = nullptr);

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
};

#endif // TIMERSETTER_H
