#include "DataInterface.hpp"

DataInterface::DataInterface()
{
    _Dbfilename = "";
    _Dbname = "";
    _DbType = QSqlDriver::DbmsType::UnknownDbms;
    _TableList = nullptr;
}

DataInterface::~DataInterface()
{
    if(_TableList != nullptr)
    {
        delete  _TableList;
    }
}

void DataInterface::setParameters(QString dbfilename, QString dbname)
{
    //If this overloaded version is called,its means a SQLite local database
    _Dbfilename = dbfilename;
    _Dbname = dbname;
    _DbType = QSqlDriver::DbmsType::SQLite;
}

void DataInterface::setParameters(QSqlDriver::DbmsType dbtype, QString server, QString dbname, QString username, QString password, quint16 port)
{
    //If this overloaded version is called, it means a full fledged RDBMS
    _DbType = dbtype;
    _Server = server;
    _Dbname = dbname;
    _Username = username;
    _Password = password;
    _Port = port;
}


bool DataInterface::open()
{
    if(_TableList != nullptr)
    {
        delete  _TableList;
    }

    if(_DbType == QSqlDriver::DbmsType::SQLite)
    {
        _Database = QSqlDatabase::addDatabase("QSQLITE");
        _Database.setDatabaseName(_Dbfilename);

         if (!_Database.open())
         {
             return  false;
         }
    }

    QStringList tabs = _Database.tables(QSql::Tables);

    _TableList = new QStringList(tabs);

    return true;
}

bool DataInterface::isOpen()
{
    return _Database.isOpen();
}

void DataInterface::close()
{
    _Database.close();
}

QSqlDatabase* DataInterface::getDatabase()
{
    return &_Database;
}

bool DataInterface::contains(const QString &tabname)
{
    if(_TableList == nullptr)
    {
        return false;
    }

    return _TableList->contains(tabname, Qt::CaseInsensitive);
}

