#ifndef EDGE_VIEW_API
#define EDGE_VIEW_API

#include <QObject>
#include <QStringBuilder>
#include <QUrlQuery>
#include <QDebug>
#include <QList>
#include <QPair>
#include <QHostAddress>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QCoreApplication>
#include "QtHttpClientWrapper.h"
#include "QtHttpServer.h"
#include "QtHttpRequest.h"
#include "QtHttpReply.h"
#include "QtHttpHeader.h"
#include "DataInterface.h"
#include "DbInit.h"
#include "RequestProcessor.h"

class EdgeViewAPIServer : public QCoreApplication
{
    Q_OBJECT
public:
    explicit EdgeViewAPIServer(int argc, char *argv[]);
    virtual ~EdgeViewAPIServer();
    bool start();
public slots:
    void onServerStopped();
    void onServerStarted(quint16 port);
    void onServerError(QString msg);
    void onClientConnected(QString guid);
    void onClientDisconnected(QString guid);
    void onRequest(QtHttpRequest *request, QtHttpReply *reply);
private:
    void createDatabase(QString &dbfilepath);
    void checkAndCreateTables(QString &dbfilepath);
    void sendServerStatus(QtHttpRequest *request, QtHttpReply *reply);
    QString base64Encode(QString &string);
    QString base64Decode(QString &string);

    void signIn(QMap<QString, QString> &postitems, QtHttpRequest *request, QtHttpReply *reply);
    void signUp(QMap<QString, QString> &postitems, QtHttpRequest *request, QtHttpReply *reply);
    void signUpVerify(QtHttpRequest *request, QtHttpReply *reply);
    void getMasterAdList(QtHttpRequest *request, QtHttpReply *reply);
    void getPendingAdList(QtHttpReply *reply, QString &username);
    void getSubmittedAdList(QtHttpReply *reply, QString &username);
    void getCreateAdPage(QtHttpRequest *request, QtHttpReply *reply);
    void getAd(QtHttpRequest *request, QtHttpReply *reply);
    void createAd(QMap<QString, QString> &postitems, QtHttpRequest *request, QtHttpReply *reply);
    void bidForAd(QMap<QString, QString> &postitems, QtHttpRequest *request, QtHttpReply *reply);
    void buyAd(QtHttpRequest *request, QtHttpReply *reply);
    void approveAd(QMap<QString, QString> &postitems, QtHttpRequest *request, QtHttpReply *reply);
    void setAdPrice(QtHttpRequest *request, QtHttpReply *reply);
    void setBanner(QtHttpRequest *request, QtHttpReply *reply);
    void getBanner(QtHttpRequest *request, QtHttpReply *reply);

    void sendFile(QtHttpRequest *request, QtHttpReply *reply);
    void sendPage(QtHttpReply *reply, QString htmlFile);
    void getFormName(QMap<QString, QString> &postitems, QString &formname);
    void getTemplatePage(const QString page, QString &pgdata);

    QtHttpServer  _Server;
    QTextStream*  _ConsoleOut;
    QString       _DataDirectory;
    QString       _WebDirectory;
    DataInterface _DataInf;
    quint16         _Port;
    QMutex          _Mutex;
    bool            _VerboseLog;
    QString         _ServerName;
    QString         _Host;
    RequestProcessor* _RequestProcessor;
};

#endif
