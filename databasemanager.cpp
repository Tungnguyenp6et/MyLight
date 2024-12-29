#include "databasemanager.h"

bool DatabaseManager::connectToDatabase(const QString &dbName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    if (!db.open()){
        qDebug() << db.lastError().text();
        return false;
    }
    qDebug() << "Successfully connect to the database";
    return true;
}

QSqlQuery DatabaseManager::executeQuery(const QString &queryStr)
{
    QSqlQuery query = QSqlQuery(db);
    if (!query.exec(queryStr)){
        qDebug() << "Query execution failed! " << query.lastError().text();
    }
    return query;
}

QSqlDatabase& DatabaseManager::getDatabase()
{
    return db;
}

DatabaseManager::DatabaseManager()
{

}

DatabaseManager::~DatabaseManager()
{
    if (db.isOpen()){
        db.close();
    }
}

