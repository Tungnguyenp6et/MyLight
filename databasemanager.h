#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    static DatabaseManager& getInstance(){
        static DatabaseManager instance;
        return instance;
    }
    bool connectToDatabase(const QString &dbName);
    QSqlQuery executeQuery(const QString &queryStr);
    QSqlDatabase& getDatabase();

private:
    DatabaseManager();
    ~DatabaseManager();
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;
    QSqlDatabase db;

signals:
};

#endif // DATABASEMANAGER_H
