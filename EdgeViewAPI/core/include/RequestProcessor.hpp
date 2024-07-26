#ifndef REQUEST_PROCESSOR_H
#define REQUEST_PROCESSOR_H

#include <QtCore/QUuid>
#include <QObject>
#include <QMutex>
#include <QTextStream>
//#include <QTextCodec>
#include <QSqlDatabase>
#include <QtGui/QPixmap>
#include <time.h>
#include "DataInterface.hpp"
#include "Users.hpp"

class RequestProcessor : public QObject
{
    Q_OBJECT
public:
    RequestProcessor(int hashseed, QTextStream* ostream, QObject *parent = Q_NULLPTR);
    RequestProcessor(int hashseed, QSqlDatabase* pdatabase, QString dataDirectory, QTextStream* ostream, QObject *parent = Q_NULLPTR);
    virtual ~RequestProcessor();
    void setInterfaces(QSqlDatabase* pdatabase, QString dataDirectory);
    bool processSignIn(QString &username, QString &password, QString &userid, QString &utype);
    bool processSignUp(QMap<QString, QString> &postitems, QString &statusmessage, QString &server);
    bool processSignUpVerify(QString &token, QString &statusmessage);

    void enableVerboseLog();
private:

    QString       _DataDirectory;
    QSqlDatabase* _Database;
    QTextStream*  _ConsoleOut;
    QMutex         _Mutex;
    bool          _VerboseLog;
};

#endif
