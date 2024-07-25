#ifndef ADS_H
#define ADS_H

#include <QObject>
#include <QtSql>
#include "DataEntity.h"

class Ads : public DataEntity
{
public:
    Ads(QSqlDatabase* db, QString tabname);
    virtual ~Ads();
    bool create(QSqlRecord record);
    bool update(QSqlRecord record);
private:
};

#endif
