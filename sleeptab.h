#ifndef SLEEPTAB_H
#define SLEEPTAB_H

#include <QObject>
#include "abstracttab.h"

class SleepTab : public AbstractTab
{
    Q_OBJECT
public:
    explicit SleepTab(QWidget *parent = nullptr);
    void OnAddButtonClicked() override;
    void OnDeleteButtonClicked() override;
};

#endif // SLEEPTAB_H
