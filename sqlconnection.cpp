#include "sqlconnection.h"

SQLConnection::SQLConnection(QObject *parent)
    : QObject{parent}
{

}
bool SQLConnection::createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    if (!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
            QObject::tr("Unable to establish a database connection.\n"
                        "This example needs SQLite support. Please read "
                        "the Qt SQL driver documentation for information how "
                        "to build it.\n\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query;
    query.exec("create table data (id int primary key, "
               "Data varchar(20), Num varchar(20))");
    query.exec("insert into data values(03, 'data', '3')");
    query.exec("insert into person values(04, 'data', '4')");

    return true;
}
