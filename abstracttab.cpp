#include "abstracttab.h"

AbstractTab::AbstractTab(QWidget *parent)
    : QWidget{parent}
{
    Layout->addWidget(MyTitle, 0, 0, 1, 3 , Qt::AlignHCenter);
    Layout->addWidget(MyView, 1, 0, 4, 3);
    Layout->addWidget(AddButton, 5, 0, 1, 1);
    Layout->addWidget(DeleteButton, 5,2,1,1);
    MyView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    AddButton->setText("ADD");
    DeleteButton->setText("DELETE");
}
bool AbstractTab::IsTimeAvailable(QString StartTime, QString EndTime, QString ID) {
    QTime startTime = QTime::fromString(StartTime);
    QTime endTime = QTime::fromString(EndTime);
    QTime midnight(23, 59, 59);
    QSqlQuery checkQuery = DatabaseManager::getInstance().executeQuery("SELECT StartTime, EndTime FROM Activities WHERE ID != " + ID );
    while (checkQuery.next()){
        QTime existedStartTime = QTime::fromString(checkQuery.value(0).toString());
        QTime existedEndTime = QTime::fromString(checkQuery.value(1).toString());
        if (startTime < endTime && existedStartTime < existedEndTime){
            if (startTime < existedEndTime && startTime > existedStartTime){
                qDebug() << "Start Time invalid";
                qDebug() << existedStartTime << existedEndTime << startTime;
                return false;
            }
            if (endTime < existedEndTime && endTime > existedStartTime){
                qDebug() << "End Time invalid";
                qDebug() << existedStartTime << existedEndTime << endTime;
                return false;
            }
            if (startTime <= existedStartTime && endTime >= existedEndTime){
                qDebug() << "Period invalid";
                qDebug() << existedStartTime << existedEndTime << startTime << endTime;
                return false;
            }
        }
        if (startTime < endTime && existedStartTime > existedEndTime){
            if (startTime > QTime(0,0)) {
                if (startTime < existedEndTime || startTime > existedStartTime){
                    qDebug() << "Start Time invalid2";
                    qDebug() << existedStartTime << existedEndTime << startTime;
                    return false;
                }
            }
            if (endTime < midnight){
                if (endTime > existedStartTime){
                    qDebug() << "End Time invalid2";

                    qDebug() << existedStartTime << existedEndTime << endTime;
                    return false;
                }
            }
        }
        if (startTime >= endTime && existedStartTime >= existedEndTime){
            qDebug() << "Period invalid2";
            return false;
        }
    }
    return true;
}

