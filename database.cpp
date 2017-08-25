#include <database.h>

myDB::myDB(QObject *parent) : QObject(parent){

    connectDB();
}

myDB::~myDB(){

}

bool myDB::connectDB(){
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("Samuel Gong");
    db.setPassword("101397.jzf");
    db.setPort(3306);
    db.setDatabaseName("library");
    if(!db.open()){
        QMessageBox::critical(0, QObject::tr("error"),  db.lastError().text());
        return false;
    }

    return true;
}
