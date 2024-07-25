#include "Ads.h"

Ads::Ads(QSqlDatabase *db, QString tabname) : DataEntity(db, tabname)
{
}

Ads::~Ads()
{
}

bool Ads::create(QSqlRecord record)
{
    return true;
}

bool Ads::update(QSqlRecord record)
{
    return true;
}
