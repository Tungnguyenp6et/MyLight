#include "timedelegate.h"

TimeDelegate::TimeDelegate(QWidget *parent) : QStyledItemDelegate(parent)
{}

QWidget *TimeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QTimeEdit *editor = new QTimeEdit(parent);
    editor->setDisplayFormat("HH:mm");
    return editor;
}

void TimeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QTimeEdit *timeEditor = qobject_cast<QTimeEdit *>(editor);
    QTime time = index.model()->data(index, Qt::EditRole).toTime();
    timeEditor->setTime(time);
}

void TimeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QTimeEdit *timeEditor = qobject_cast<QTimeEdit*>(editor);
    timeEditor->interpretText();
    QTime time = timeEditor->time();
    QString timeStr = time.toString();
    model->setData(index, timeStr, Qt::EditRole);
}
