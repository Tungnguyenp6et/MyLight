#ifndef TIMEDELEGATE_H
#define TIMEDELEGATE_H

#include <QStyledItemDelegate>
#include <QWidget>
#include <QTimeEdit>
#include <QTime>
class TimeDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    TimeDelegate(QWidget *parent);
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif // TIMEDELEGATE_H
