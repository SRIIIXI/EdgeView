#include "AdsLocal.h"

AdsLocal::AdsLocal(QSqlDatabase *db, QString tabname) : DataEntity(db, tabname)
{
}

AdsLocal::~AdsLocal()
{
}

bool AdsLocal::create(QSqlRecord record)
{
    return true;
}

bool AdsLocal::update(QSqlRecord record)
{
    return true;
}
