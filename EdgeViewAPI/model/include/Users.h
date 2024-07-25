#ifndef USERS_H
#define USERS_H

#include <QObject>
#include <QtSql>
#include "DataEntity.h"

class Users : public DataEntity
{
public:
    Users(QSqlDatabase* db, QString tabname);
    virtual ~Users();
    bool create(QSqlRecord record);
    bool update(QSqlRecord record);
private:
};

#endif
