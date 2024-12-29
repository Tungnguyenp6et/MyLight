#ifndef ABSTRACTTAB_H
#define ABSTRACTTAB_H

#include <QWidget>
#include <QTableView>
#include <QSqlTableModel>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QTime>
#include <QHeaderView>
#include <QModelIndex>
#include <QMessageBox>
#include "databasemanager.h"
#include "timedelegate.h"
class AbstractTab : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractTab(QWidget *parent = nullptr);

    virtual void OnAddButtonClicked() = 0;
    virtual void OnDeleteButtonClicked() = 0;




    bool IsTimeAvailable(QString Start_Time, QString End_Time, QString ID);

    QTableView *MyView = new QTableView(this);
    QSqlTableModel *MyModel = new QSqlTableModel(this, DatabaseManager::getInstance().getDatabase());
    QLabel *MyTitle = new QLabel(this);
    QPushButton *AddButton = new QPushButton(this);
    QPushButton *DeleteButton = new QPushButton(this);
    QGridLayout *Layout = new QGridLayout(this);
    TimeDelegate *timeDelegate = new TimeDelegate(this);
signals:
};

#endif // ABSTRACTTAB_H
