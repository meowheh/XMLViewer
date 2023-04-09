#ifndef SQLCONNECTION_H
#define SQLCONNECTION_H

#include <QObject>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class SQLConnection : public QObject
{
    Q_OBJECT
public:
    explicit SQLConnection(QObject *parent = nullptr);

public slots:
    static bool createConnection();
signals:

};

#endif // SQLCONNECTION_H
