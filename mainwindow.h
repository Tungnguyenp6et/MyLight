#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include "databasemanager.h"
#include "playtab.h"
#include "sleeptab.h"
#include "workingtab.h"
#include "alarm.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QDebug>
#include <QUrl>
#include <QEventLoop>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void DatabaseSetup();
    void OnSaveButtonClicked();
    void OnStopButtonClicked();
    void Post(QUrl url, QByteArray array);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTabWidget *TabControl = new QTabWidget(this);
    PlayTab *playTab;
    SleepTab *sleepTab;
    WorkingTab *workTab;
    Alarm *alarm;
    QPushButton *SaveButton = new QPushButton(this);
    QPushButton *StopButton = new QPushButton(this);
    QGridLayout *Layout = new QGridLayout(this);
    QWidget *CentralWidget = new QWidget(this);
    QUrl sleepUrl;
    QUrl workUrl;
    QUrl playUrl;
    QUrl endUrl;
    QByteArray command;

signals:
    void StopButtonClicked();
};
#endif // MAINWINDOW_H
