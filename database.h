
#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
class MainWindow;

class myDB : public QObject{
    Q_OBJECT

public:
    myDB(QObject *parent = 0);
    ~myDB();
    friend class MainWindow;
private:
    QSqlDatabase db;
    bool connectDB();
};


#endif // DATABASE_H
