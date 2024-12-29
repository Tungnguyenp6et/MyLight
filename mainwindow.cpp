#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DatabaseSetup();
    this->setMaximumHeight(400);
    this->setMaximumWidth(400);
    sleepTab = new SleepTab(this);
    workTab = new WorkingTab(this);
    playTab = new PlayTab(this);

    sleepUrl = QUrl("http://192.168.4.1/sleeptime");
    workUrl = QUrl("http://192.168.4.1/worktime");
    playUrl = QUrl("http://192.168.4.1/playtime");
    endUrl = QUrl("http://192.168.4.1/endtime");
    command.append("command=somecommand");


    alarm = new Alarm(this);

    TabControl->addTab(sleepTab, "Sleeping Routine");

    TabControl->addTab(workTab, "Working Routine");

    TabControl->addTab(playTab, "Playing Routine");

    Layout->addWidget(TabControl, 0, 0, 6, 4);

    Layout->addWidget(SaveButton, 7,0, 1,1);

    Layout->addWidget(StopButton, 7, 3, 1, 1 );

    SaveButton->setText("SAVE");

    StopButton->setText("STOP");

    CentralWidget->setLayout(Layout);

    this->setCentralWidget(CentralWidget);

    TabControl->setStyleSheet("QTabBar::tab { width: 100%; }");


    QObject::connect(SaveButton, &QPushButton::clicked, this, &MainWindow::OnSaveButtonClicked);

    QObject::connect(StopButton, &QPushButton::clicked, this, &MainWindow::OnStopButtonClicked);

}


void MainWindow::OnSaveButtonClicked(){
    alarm->checkAlarm();

    TabControl->setEnabled(false);

    QObject::connect(alarm, &Alarm::workSignal, this, [=](int remainedSecond){


        QMessageBox::information(this, "yeah", "Work hours within " + QString::number(remainedSecond));

        Post(workUrl, command);

        QTimer *workTimer = new QTimer;

        workTimer->start(remainedSecond*1000);

        QObject::connect(workTimer, &QTimer::timeout, workTimer, &QObject::deleteLater);

        QObject::connect(workTimer, &QTimer::timeout, alarm, &Alarm::checkAlarm);

        QObject::connect(this, &MainWindow::StopButtonClicked, workTimer, &QTimer::stop);

        QObject::connect(this, &MainWindow::StopButtonClicked, workTimer, &QTimer::deleteLater);

        QObject::connect(workTimer, &QTimer::timeout, this, [=](){
            QMessageBox::information(this, "yeah", "Done Work");
            Post(endUrl, command);
        });

    });
    QObject::connect(alarm, &Alarm::sleepSignal, this, [=](int remainedSecond){

        Post(sleepUrl, command);
        QMessageBox::information(this, "yeah", "Sleep hours within " + QString::number(remainedSecond));

        QTimer *workTimer = new QTimer;

        workTimer->start(remainedSecond*1000);

        QObject::connect(workTimer, &QTimer::timeout, workTimer, &QObject::deleteLater);

        QObject::connect(workTimer, &QTimer::timeout, alarm, &Alarm::checkAlarm);

        QObject::connect(workTimer, &QTimer::timeout, this, [=](){
            Post(endUrl, command);
            QMessageBox::information(this, "yeah", "Done Sleep");
        });

        QObject::connect(this, &MainWindow::StopButtonClicked, workTimer, &QTimer::stop);

        QObject::connect(this, &MainWindow::StopButtonClicked, workTimer, &QTimer::deleteLater);
    });
    QObject::connect(alarm, &Alarm::playSignal, this, [=](int remainedSecond){
        Post(playUrl, command);

        QMessageBox::information(this, "yeah", "Play hours within " + QString::number(remainedSecond));

        QTimer *workTimer = new QTimer;

        workTimer->start(remainedSecond*1000);

        QObject::connect(workTimer, &QTimer::timeout, workTimer, &QObject::deleteLater);

        QObject::connect(workTimer, &QTimer::timeout, alarm, &Alarm::checkAlarm);

        QObject::connect(workTimer, &QTimer::timeout, this, [=](){
            Post(endUrl, command);
            QMessageBox::information(this, "yeah", "Done Play");
        });
        QObject::connect(this, &MainWindow::StopButtonClicked, workTimer, &QTimer::stop);

        QObject::connect(this, &MainWindow::StopButtonClicked, workTimer, &QTimer::deleteLater);
    });
    return;
}

void MainWindow::OnStopButtonClicked(){
    TabControl->setEnabled(true);
    alarm->stopAlarm();
    emit StopButtonClicked();
    return;
}

void MainWindow::Post(QUrl url, QByteArray array)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QNetworkAccessManager manager;

    QNetworkReply *reply = manager.post(request, array);

    QEventLoop eventLoop;
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec(); // Wait for the request to finish

    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "Post successfully:" << reply->readAll();
    } else {
        qDebug() << reply->errorString();
    }

}


//Simply set up the database
void MainWindow::DatabaseSetup()
{
    DatabaseManager::getInstance().connectToDatabase("MyRoutine.db");
    // Create table store and sort all activities
    DatabaseManager::getInstance().executeQuery("CREATE TABLE IF NOT EXISTS Activities (ID INTEGER PRIMARY KEY AUTOINCREMENT, StartTime TEXT, EndTime TEXT, Activity TEXT);");
}

MainWindow::~MainWindow()
{
    delete ui;
}
