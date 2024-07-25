#ifndef DB_INIT_H
#define DB_INIT_H

#include <QObject>
#include <QtSql>
#include <QDir>
#include <QStringList>

class DbInit
{
public:
    DbInit();
    virtual ~DbInit();
    bool createFile(const QString &dbfilename);
    bool openDatabase(const QString &dbfilename);
    bool contains(const QString &tabname);
    bool createProducts();
    bool createPages();
    bool createUsers();
    bool createJournalEntries();
    bool createSales();
    bool createLogins();
    bool createAds();
    bool createAdsLocal();
    QString* getError();
private:
    bool executeSQL();
    QSqlDatabase    _Dbase;
    QString         _SqlString;
    QString         _ErrString;
    QStringList*    _TableList;
};

#endif
