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
#include "DataInterface.h"
#include "Users.h"
#include "Ads.h"
#include "AdsLocal.h"

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

    bool processGetPendingAdList(QString &username, QString &adlist);
    bool processGetSubmittedAdList(QString &username, QString &adlist);
    bool processGetMasterAdList(QString &adlist);
    bool processGetAd(QString &adid, QString &addetails);
    bool processGetMasterAd(QString &adid, QString &addetails);
    bool processCreateAd(QMap<QString, QString> &postitems, QString &publisher, QString &statusmessage);
    bool processBidForAd(QMap<QString, QString> &postitems, QString &statusmessage);
    bool processApproveAd(QString &adid, QString &apprflag, QString &apprtext, QString &statusmessage);
    bool processSetAdPrice(QString &adid, QString &price, QString &statusmessage);
    bool processUpdateBanner(QString &adid, QByteArray &imagedata, QString &ftype, QString &statusmessage);
    bool processGetBanner(QString &fname, QByteArray &imagedata);
    void enableVerboseLog();
private:

    QString       _DataDirectory;
    QSqlDatabase* _Database;
    QTextStream*  _ConsoleOut;
    QMutex         _Mutex;
    bool          _VerboseLog;
};

#endif
