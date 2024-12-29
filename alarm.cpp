#include "alarm.h"

Alarm::Alarm(QObject *parent)
    : QObject{parent}
{
    connect(checkTimer, &QTimer::timeout, this, &Alarm::checkAlarm);
}
void Alarm::checkAlarm(){
    QSqlQuery alarmQuery = DatabaseManager::getInstance().executeQuery("Select StartTime, EndTime, Activity FROM ACTIVITIES");
    while (alarmQuery.next()){
        QTime startTime = QTime::fromString(alarmQuery.value(0).toString());
        QTime endTime  = QTime::fromString(alarmQuery.value(1).toString());
        QString activity = alarmQuery.value(2).toString();
        if (startTime < endTime){
            if (QTime::currentTime() >= startTime && QTime::currentTime() <= endTime){
                int remainedSecond = QTime::currentTime().secsTo(endTime);
                if (activity == "Work"){
                    emit workSignal(remainedSecond);
                    return;
                }
                else if (activity == "Sleep") {
                    emit sleepSignal(remainedSecond);
                    return;
                }
                else if (activity == "Play"){
                    emit playSignal(remainedSecond);
                    return;
                }
            }
        }
        if (startTime > endTime){
            int remainedSecond;
            if (QTime::currentTime() >= startTime){
                remainedSecond = QTime::currentTime().secsTo(QTime(23,59,59)) + QTime(0,0,0).secsTo(endTime);
            }
            if (QTime::currentTime() > QTime(0,0,0) && QTime::currentTime() < endTime){
                remainedSecond = QTime::currentTime().secsTo(endTime);
            }
            if (activity == "Work"){
                emit workSignal(remainedSecond);
                return;
            }
            else if (activity == "Sleep") {
                emit sleepSignal(remainedSecond);
                return;
            }
            else if (activity == "Play"){
                emit playSignal(remainedSecond);
                return;
            }
        }
    }
    checkTimer->start(1000);
}
void Alarm::stopAlarm(){
        if (checkTimer->isActive()){
            checkTimer->stop();
        }
}

