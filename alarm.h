#ifndef ALARM_H
#define ALARM_H

#include <QObject>
#include <QTime>
#include <QTimer>
#include "databasemanager.h"

class Alarm : public QObject
{
    Q_OBJECT
public:
    explicit Alarm(QObject *parent = nullptr);

    void checkAlarm();
    void stopAlarm();
    QTimer *checkTimer = new QTimer(this);


signals:
    void workSignal(int second);
    void sleepSignal(int second);
    void playSignal(int second);
};

#endif // ALARM_H
