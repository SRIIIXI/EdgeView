#include "DbInit.h"

DbInit::DbInit()
{
    _TableList = nullptr;
}

DbInit::~DbInit()
{
    _Dbase.close();
    if(_TableList != nullptr)
    {
        delete  _TableList;
    }
}

bool DbInit::createFile(const QString &dbfilename)
{
    QString temp = dbfilename;

    QDir dir;

    QFileInfo finfo(dbfilename);

    QString pstr = finfo.baseName() + "." + finfo.completeSuffix();

    QString path = temp.remove(pstr, Qt::CaseSensitivity::CaseSensitive);

    if(!dir.mkpath(path))
    {
        return false;
    }

    QFile fl(dbfilename);

    if(!fl.open(QIODevice::ReadWrite))
    {
        return false;
    }

    fl.close();

    _Dbase = QSqlDatabase::addDatabase("QSQLITE");

    return true;
}

bool DbInit::openDatabase(const QString &dbfilename)
{
    _Dbase = QSqlDatabase::addDatabase("QSQLITE");
    _Dbase.setDatabaseName(dbfilename);

    if(!_Dbase.open())
    {
        return false;
    }

    _SqlString = "USE goshtv";

    if(!executeSQL())
    {
        return false;
    }

    QStringList tabs = _Dbase.tables(QSql::Tables);

    _TableList = new QStringList(tabs);

    return true;
}

bool DbInit::contains(const QString &tabname)
{
    if(_TableList == nullptr)
    {
        return false;
    }

    return _TableList->contains(tabname, Qt::CaseInsensitive);
}

bool DbInit::createProducts()
{
    _SqlString = "CREATE TABLE Products \
            (	\
            Sku unsigned int auto increment PRIMARY KEY, \
            Media varchar(1), \
            Title varchar(32), \
            Description varchar(32), \
            Price smallmoney, \
            QtySold int \
            )";

    if(!executeSQL())
    {
        return false;
    }

    return true;
}

bool DbInit::createPages()
{
    _SqlString = "CREATE TABLE Pages \
            (	\
            Sku unsigned int NOT NULL, \
            Page smallint NOT NULL, \
            Description varchar(32), \
            PRIMARY KEY(Sku,Page) \
            )";

    if(!executeSQL())
    {
        return false;
    }

    return true;
}

bool DbInit::createUsers()
{
    _SqlString = "CREATE TABLE Users \
            ( \
            UserId unsigned int auto increment PRIMARY KEY, \
            Username varchar(32), \
            Lastname varchar(32), \
            Firstname varchar(32), \
            Email varchar(32), \
            Phone varchar(32), \
            Denomination varchar(2), \
            Balance smallmoney, \
            Password varchar(32) \
            )";

    if(!executeSQL())
    {
        return false;
    }

   _SqlString = "insert into users (userid, username, email, password, firstname, lastname) values(111111, 'admin', 'admin@gohstv', 'goshtvadmin', 'Administrator', 'Administrator')";

    if(!executeSQL())
    {
        return false;
    }

    return true;
}

bool DbInit::createJournalEntries()
{
    _SqlString = "CREATE TABLE JournalEntries \
            (	\
            SaleId unsigned int, \
            UserId unsigned int, \
            Sku unsigned int, \
            Denomination varchar(2), \
            Price smallmoney, \
            Balance smallmoney, \
            PRIMARY KEY (SaleId) \
            )";

    if(!executeSQL())
    {
        return false;
    }

    return true;
}

bool DbInit::createSales()
{
    _SqlString = "CREATE TABLE Sales \
            (	\
            SaleId unsigned int auto increment, \
            UserId unsigned int, \
            Sku unsigned int, \
            Note varchar(32), \
            WhenLogged timestamp, \
            Denomination varchar(2), \
            Price smallmoney, \
            PRIMARY KEY (SaleId) \
            )";

    if(!executeSQL())
    {
        return false;
    }

    return true;
}

bool DbInit::createLogins()
{
    _SqlString = "CREATE TABLE Logins \
            (	\
            LoginId unsigned int auto increment PRIMARY KEY, \
            Status varchar(1) NOT NULL, \
            WhenLogged timestamp, \
            Ip1 unsigned int NOT NULL, \
            Ip2 unsigned int NOT NULL, \
            Ip3 unsigned int NOT NULL, \
            Ip4 unsigned int NOT NULL \
            )";

    if(!executeSQL())
    {
        return false;
    }

    return true;
}

bool DbInit::createAds()
{
    _SqlString = "CREATE TABLE Ads \
            (	\
            AdId unsigned int auto increment PRIMARY KEY, \
            UserId unsigned int NOT NULL, \
            Url varchar(1), \
            Description varchar(32),\
            Price smallmoney \
            )";

    if(!executeSQL())
    {
        return false;
    }

    return true;
}

bool DbInit::createAdsLocal()
{
    _SqlString = "CREATE TABLE AdsLocal \
            ( \
            AdId unsigned int auto increment PRIMARY KEY, \
            UserId unsigned int NOT NULL, \
            Url varchar(1), \
            Description varchar(32), \
            Price smallmoney \
            )";

    if(!executeSQL())
    {
        return false;
    }

    return true;
}

bool DbInit::executeSQL()
{
    QSqlQuery qryresult;

    try
    {
        _Dbase.transaction();

        qryresult = _Dbase.exec(_SqlString);

        _Dbase.commit();
    }
    catch(QException e)
    {
       _Dbase.rollback();
       _ErrString = _Dbase.lastError().text();
       return false;
    }

    return true;
}

QString* DbInit::getError()
{
    return &_ErrString;
}

