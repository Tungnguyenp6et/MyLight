#ifndef WORKINGTAB_H
#define WORKINGTAB_H

#include <QObject>
#include "abstracttab.h"

class WorkingTab : public AbstractTab
{
    Q_OBJECT
public:
    explicit WorkingTab(QWidget *parent = nullptr);
    void OnAddButtonClicked() override;
    void OnDeleteButtonClicked() override;
};

#endif // WORKINGTAB_H
