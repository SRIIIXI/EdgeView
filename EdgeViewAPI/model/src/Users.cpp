#include "Users.h"

Users::Users(QSqlDatabase *db, QString tabname) : DataEntity(db, tabname)
{
}

Users::~Users()
{
}

bool Users::create(QSqlRecord record)
{
    return true;
}

bool Users::update(QSqlRecord record)
{
    return true;
}
