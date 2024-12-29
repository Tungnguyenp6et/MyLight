#ifndef PLAYTAB_H
#define PLAYTAB_H

#include <QObject>
#include "abstracttab.h"

class PlayTab : public AbstractTab
{
    Q_OBJECT
public:
    PlayTab(QWidget *parent = nullptr);
    void OnAddButtonClicked() override;
    void OnDeleteButtonClicked() override;
};

#endif // PLAYTAB_H
