#include "workingtab.h"

WorkingTab::WorkingTab(QWidget *parent) : AbstractTab(parent) {
    this->MyTitle->setText("<b>Your Working Routine<\b>");

    this->MyModel->setTable("Activities");

    this->MyView->setModel(MyModel);
    MyModel->setFilter("Activity = 'Work'");
    MyModel->select();
    MyView->reset();
    MyModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    MyView->hideColumn(0);
    MyView->hideColumn(3);
    MyView->setItemDelegateForColumn(1,this->timeDelegate);
    MyView->setItemDelegateForColumn(2,this->timeDelegate);

    connect(AddButton, &QPushButton::clicked, this, &WorkingTab::OnAddButtonClicked);
    connect(DeleteButton, &QPushButton::clicked, this, &WorkingTab::OnDeleteButtonClicked);
    connect(MyModel, &QSqlTableModel::dataChanged, [=](const QModelIndex &topLeft,
                                                       const QModelIndex &bottomRight, const QList<int> &roles = QList<int>()){
        Q_UNUSED(bottomRight);
        Q_UNUSED(roles);
        const int SECONDS_IN_30_MINUTES = 30 * 60;
        if (topLeft.column() == 1) {
            QModelIndex endIndex = MyModel->index(topLeft.row(), 2);
            if (MyModel->data(endIndex).isNull()) {
                MyModel->submit();
                QTime endTime = QTime::fromString(MyModel->data(topLeft).toString()).addSecs(SECONDS_IN_30_MINUTES);
                qDebug() << endTime;
                MyModel->setData(endIndex, endTime.toString("HH:mm"));
                MyView->reset();
            }
        }
        if (topLeft.column() == 2) {
            QModelIndex endIndex = MyModel->index(topLeft.row(), 1);
            if (MyModel->data(endIndex).isNull()) {
                MyModel->submit();
                QTime endTime = QTime::fromString(MyModel->data(topLeft).toString()).addSecs(-SECONDS_IN_30_MINUTES);
                qDebug() << endTime;
                MyModel->setData(endIndex, endTime.toString("HH:mm"));
                MyView->reset();
            }
        }
        if (topLeft.column() == 1 || topLeft.column() == 2 ) {
            QModelIndex startIndex = MyModel->index(topLeft.row(), 1);
            QModelIndex endIndex = MyModel->index(topLeft.row(), 2);
            QString Start_Time = MyModel->data(startIndex).toString();
            QString End_Time = MyModel->data(endIndex).toString();
            QString ID = MyModel->data(MyModel->index(topLeft.row(), 0)).toString();
            if (IsTimeAvailable(Start_Time, End_Time, ID)){
                return;
            }
            else {
                QMessageBox::information(nullptr, "NO", "Time overlap" + ID);
                MyModel->revertAll();
            }
        }
    });

}
void WorkingTab::OnAddButtonClicked()
{
    int row = MyModel->rowCount();
    MyModel->insertRow(row, QModelIndex());
    QModelIndex index = MyModel->index(row, 3, QModelIndex());
    MyModel->setData(index, "Work");
}

void WorkingTab::OnDeleteButtonClicked()
{
    QModelIndex index = MyView->currentIndex();
    MyModel->removeRow(index.row(), QModelIndex());
}
