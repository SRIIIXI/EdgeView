#ifndef ADS_LOCAL_H
#define ADS_LOCAL_H

#include <QObject>
#include <QtSql>
#include "DataEntity.h"

class AdsLocal : public DataEntity
{
public:
    AdsLocal(QSqlDatabase* db, QString tabname);
    virtual ~AdsLocal();
    bool create(QSqlRecord record);
    bool update(QSqlRecord record);
private:
};

#endif
