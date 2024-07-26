#include "EdgeViewAPIServer.hpp"

EdgeViewAPIServer::EdgeViewAPIServer(int argc, char *argv[]) : QCoreApplication (argc, argv)
{
    _Port = 8080;
    _ConsoleOut = new QTextStream(stdout);
    _VerboseLog = false;
    _ServerName = "EdgeViewAPI Server";
    _RequestProcessor = nullptr;
    _Host = "";

    connect (&_Server, &QtHttpServer::started,            this, &EdgeViewAPIServer::onServerStarted);
    connect (&_Server, &QtHttpServer::stopped,            this, &EdgeViewAPIServer::onServerStopped);
    connect (&_Server, &QtHttpServer::error,              this, &EdgeViewAPIServer::onServerError);
    connect (&_Server, &QtHttpServer::clientConnected,    this, &EdgeViewAPIServer::onClientConnected);
    connect (&_Server, &QtHttpServer::clientDisconnected, this, &EdgeViewAPIServer::onClientDisconnected);
    connect (&_Server, &QtHttpServer::requestNeedsReply,  this, &EdgeViewAPIServer::onRequest);
}

EdgeViewAPIServer::~EdgeViewAPIServer()
{
    _Server.stop();
}

bool EdgeViewAPIServer::start()
{
    *_ConsoleOut << "EdgeViewAPI Server v1.0" << Qt::endl;

    QStringList iplist;

    QList<QNetworkInterface> ifs = QNetworkInterface::allInterfaces();

    for (int ni = 0; ni < ifs.size(); ni++)
    {
        QNetworkInterface ninf = ifs[ni];

        if(!ninf.humanReadableName().toLower().contains("ethernet") && !ninf.humanReadableName().toLower().contains("wi-fi"))
        {
            continue;
        }

        QList<QNetworkAddressEntry> addrs = ninf.addressEntries();

        for(int idx = 0; idx < addrs.size(); idx++)
        {
            QNetworkAddressEntry ent = addrs[idx];

            if(ent.ip().protocol() != QAbstractSocket::IPv4Protocol || ent.ip().isLoopback())
            {
                continue;
            }

            iplist.append(ent.ip().toString());
        }
    }

    QList<QHostAddress> list = QHostInfo::fromName(QHostInfo::localHostName()).addresses();

    for (int i = 0; i < list.size(); i++)
    {
        QHostAddress addr = list[i];

        if(addr.protocol() != QAbstractSocket::IPv4Protocol || addr.isLoopback())
        {
            continue;
        }

        QString ip = list[i].toString();


        if(iplist.contains(ip))
        {
            _Host = ip;
        }
    }

    *_ConsoleOut << "Current host is " << _Host << ":" << QVariant(_Port).toString() << Qt::endl;

    QString genericlocation = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    QString databsfile = genericlocation + "/EdgeViewAPI/database/EdgeView.db";
    _DataDirectory = genericlocation + "/EdgeViewAPI/web/";
    _WebDirectory = genericlocation + "/EdgeViewAPI/web/form/";

    _VerboseLog = true;

    *_ConsoleOut << "Database file is ... " + databsfile << Qt::endl;
    *_ConsoleOut << "Data directory is ... " + _DataDirectory << Qt::endl;
    *_ConsoleOut << "Web directory is ... " + _WebDirectory << Qt::endl;

    QDir dirweb(_WebDirectory);

    if(!dirweb.exists(_WebDirectory))
    {
        *_ConsoleOut << _WebDirectory + " does not exist, returning" << Qt::endl;
        return false;
    }

    if(!dirweb.exists(_DataDirectory))
    {
        *_ConsoleOut << _WebDirectory + " does not exist, creating new" << Qt::endl;
        dirweb.mkdir(_DataDirectory);
    }

    if(!dirweb.exists(_DataDirectory+"/cache/"))
    {
        *_ConsoleOut << _DataDirectory+"/cache/" + " does not exist, creating new" << Qt::endl;
        dirweb.mkdir(_DataDirectory+"/cache/");
    }
    else
    {
        QDir cachedir(_DataDirectory+"/cache/");

        QFileInfoList flist = cachedir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot,QDir::NoSort);

        for(int fdx = 0; fdx < flist.count(); fdx++)
        {
            QString fstr = flist[fdx].absoluteFilePath();
            cachedir.remove(fstr);
        }
    }

    if(!QFileInfo::exists(databsfile))
    {
        *_ConsoleOut << databsfile + " does not exist, creating new" << Qt::endl;
        createDatabase(databsfile);
    }

    checkAndCreateTables(databsfile);

    _DataInf.setParameters(databsfile, "edgeview");

    if(!_DataInf.open())
    {
        return false;
    }

    _Server.setServerName(_ServerName);
    _Server.start (_Port);

    _RequestProcessor = new RequestProcessor(_Port, _DataInf.getDatabase(), _DataDirectory, _ConsoleOut, this);

    return true;
}

void EdgeViewAPIServer::onServerStarted(quint16 port)
{
    *_ConsoleOut << "QtHttpServer started on port " << port <<  " " << _ServerName << Qt::endl;
}

void EdgeViewAPIServer::onServerStopped()
{
    *_ConsoleOut << "QtHttpServer stopped " << _ServerName << Qt::endl;
}

void EdgeViewAPIServer::onServerError(QString msg)
{
    *_ConsoleOut << "QtHttpServer error :" << msg << Qt::endl;
}

void EdgeViewAPIServer::onClientConnected(QString guid)
{
}

void EdgeViewAPIServer::onClientDisconnected(QString guid)
{
}

void EdgeViewAPIServer::getFormName(QMap<QString, QString> &postitems, QString &formname)
{
    formname = "";

    if(postitems.contains("form_id"))
    {
        formname = postitems.value("form_id");
        return;
    }
}

void EdgeViewAPIServer::onRequest(QtHttpRequest * request, QtHttpReply * reply)
{
    QMap<QString, QString> postitems;

    QString url = request->getUrl().path();

    if(request->getCommand() == "GET")
    {
        if(url.contains(".htm") || url.contains(".js") || url.contains(".css") || url.contains(".png") || url.contains(".jpg") || url.contains(".gif") || url.contains(".ico") || url == "/")
        {
            sendFile(request, reply);
            return;
        }
    }

    if(request->getCommand() == "POST")
    {
        //QString data = QTextCodec::codecForMib(106)->toUnicode(request->getRawData());
        QString data = request->getRawData().toStdString().c_str();
        data = data.replace("%3D", "=");
        data = data.replace("%3A", ":");
        data = data.replace("%2F", "/");
        data = data.replace("%3B", ";");
        data = data.replace("%2C", ",");
        QStringList params = data.split('&');

        int ct = params.count();

        for(int idx = 0; idx < ct; idx++)
        {
                int pos = params[idx].indexOf('=');
                QString elementname = params[idx].left(pos);
                QString elementvalue = params[idx].right(params[idx].length() - (pos+1));
                postitems.insert(elementname, elementvalue);
        }
    }

    QString formname;

    getFormName(postitems, formname);

    if(formname == "login" || url.contains("signin"))
    {
        signIn(postitems, request, reply);
        return;
    }

    if(url.contains("signup"))
    {
        signUp(postitems, request, reply);
        return;
    }

    /*
    if(!request->getClient()->isAuthenticated())
    {
        signIn(request, reply);
        return;
    }
    */

    reply->setStatusCode(QtHttpReply::BadRequest);
    *_ConsoleOut << "QtHttpServer client request :" << request << Qt::endl;
}

void EdgeViewAPIServer::signIn(QMap<QString, QString> &postitems, QtHttpRequest *request, QtHttpReply *reply)
{
    bool loginstate = false;

    QString loginid = "";
    QString password = "";
    QString userid = "";
    QString usertype = "";

    if(postitems.contains("loginid"))
    {
        loginid = postitems.value("loginid");

        if(postitems.contains("password"))
        {
            password = postitems.value("password");

            loginstate = _RequestProcessor->processSignIn(loginid, password, userid, usertype);
        }
    }

    if(loginstate)
    {
        if(usertype == "X")
        {
            sendServerStatus(request, reply);
        }

        request->getClient()->setUserName(loginid);
    }
    else
    {
        QString pgdata = "";
        getTemplatePage("form_signin.html", pgdata);
        pgdata = pgdata.replace("<!--_ERROR_MESSAGE_PLACE_HOLDER_-->", "<li><label style=\"color:red\">Your Login Id or Password is invalid</label></li>");
        reply->setStatusCode(QtHttpReply::Ok);
        QByteArray buffer((const char*)pgdata.toStdString().c_str(), pgdata.toStdString().length());
        reply->appendRawData(buffer);
    }

    return;
}

void EdgeViewAPIServer::signUp(QMap<QString, QString> &postitems, QtHttpRequest *request, QtHttpReply *reply)
{
    QString server = "http://" + _Host + ":" + QVariant(_Port).toString() + "/";
    QString statusmessage = "";

    bool ret = _RequestProcessor->processSignUp(postitems, statusmessage, server);

    QString pgdata = "";

    if(ret)
    {
        getTemplatePage("form_signup_success.html", pgdata);
        pgdata = pgdata.replace("_MESSAGE_", statusmessage);
    }
    else
    {
        getTemplatePage("form_signup_error.html", pgdata);
        pgdata = pgdata.replace("<!--_ROW_PLACE_HOLDER_-->", statusmessage);
    }

    reply->setStatusCode(QtHttpReply::Ok);
    QByteArray buffer((const char*)pgdata.toStdString().c_str(), pgdata.toStdString().length());
    reply->appendRawData(buffer);
}

void EdgeViewAPIServer::signUpVerify(QtHttpRequest *request, QtHttpReply *reply)
{
    QString statusmessage = "";
    QString token;
    _RequestProcessor->processSignUpVerify(token, statusmessage);
    QByteArray buffer((const char*)statusmessage.toStdString().c_str(), statusmessage.toStdString().length());
    reply->appendRawData(buffer);
}

void EdgeViewAPIServer::sendPage(QtHttpReply *reply, QString htmlFile)
{
    char ctype[32] = {0};
    strcat(ctype, "text/html");

    QString fname = _WebDirectory + htmlFile;

    QFile file(fname);

    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();
        reply->addHeader("Content-Type", QByteArray(ctype, strlen(ctype)));
        reply->appendRawData(data);
    }
}

void EdgeViewAPIServer::getTemplatePage(const QString page, QString &pgdata)
{
    char ctype[32] = {0};
    strcat(ctype, "text/html");

    QString fname = _WebDirectory + page;

    QFile file(fname);

    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();
        //pgdata = QTextCodec::codecForMib(106)->toUnicode(data);
        pgdata = data.toStdString().c_str();
    }
}

void EdgeViewAPIServer::sendFile(QtHttpRequest *request, QtHttpReply *reply)
{
    char ctype[32] = {0};

    QString url = request->getUrl().path();

    QString fname = "";

    if(url == "/")
    {
       fname = _WebDirectory + "/login.html";
    }
    else
    {
        if(url.contains("ads"))
        {
            fname = _DataDirectory + url;
        }
        else
        {
            fname = _WebDirectory + url;
        }
    }

    int pos = fname.indexOf('.');

    if(pos >= 0)
    {
        QString ext = fname.right(fname.length() - (pos+1));

        if(ext == "html" || ext == "css" || ext == "js")
        {
            strcat(ctype, "text/");
        }
        else
        {
            strcat(ctype, "image/");
        }

        strcat(ctype, ext.toStdString().c_str());
    }

    QFile file(fname);

    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();
        reply->addHeader("Content-Type", QByteArray(ctype, strlen(ctype)));
        reply->appendRawData(data);
    }
}

void EdgeViewAPIServer::createDatabase(QString &dbfilepath)
{
    DbInit dinit;

    if(!dinit.createFile(dbfilepath))
    {
        *_ConsoleOut << "Could not create database"<< Qt::endl;
    }
}

void EdgeViewAPIServer::checkAndCreateTables(QString &dbfilepath)
{
    DbInit dinit;
    dinit.openDatabase(dbfilepath);

    if(!dinit.contains("ads"))
    {
        if(!dinit.createAds())
        {
            *_ConsoleOut << "Could not create ads"<< Qt::endl;
        }
    }

    if(!dinit.contains("adslocal"))
    {
        if(!dinit.createAdsLocal())
        {
            *_ConsoleOut << "Could not create adslocal"<< Qt::endl;
        }
    }

    if(!dinit.contains("users"))
    {
        if(!dinit.createUsers())
        {
            *_ConsoleOut << "Could not create users"<< Qt::endl;
    }
    }

    if(!dinit.contains("journalentries"))
    {
        if(!dinit.createJournalEntries())
        {
            *_ConsoleOut << "Could not create journalentries"<< Qt::endl;
        }
    }

    if(!dinit.contains("sales"))
    {
        if(!dinit.createSales())
        {
            *_ConsoleOut << "Could not create sales"<< Qt::endl;
        }
    }

    if(!dinit.contains("logins"))
    {
        if(!dinit.createLogins())
        {
            *_ConsoleOut << "Could not create logins"<< Qt::endl;
        }
    }
}

QString EdgeViewAPIServer::base64Encode(QString &string)
{
    QByteArray ba;
    ba.append(string.toLatin1());
    return ba.toBase64();
}

QString EdgeViewAPIServer::base64Decode(QString &string)
{
    QByteArray ba;
    ba.append(string.toLatin1());
    return QByteArray::fromBase64(ba);
}

void EdgeViewAPIServer::sendServerStatus(QtHttpRequest *request, QtHttpReply *reply)
{
    QString pgdata = "";
    QString temp = "";
    QDateTime dt = QDateTime::currentDateTimeUtc();

    getTemplatePage("form_index.html", pgdata);

    pgdata = pgdata.replace("_HEADING_", "EdgeViewAPI : Administrator Login");
    temp = request->getHeader (QtHttpHeader::Host);
    pgdata = pgdata.replace("_LINE1_", "Virtual host : " + temp);
    temp = request->getHeader (QtHttpHeader::UserAgent);
    pgdata = pgdata.replace("_LINE2_", "Your User-Agent : " + temp);
    pgdata = pgdata.replace("_LINE3_", "Server : " + _Host + ":" + QVariant(_Port).toString());
    temp = dt.toString(Qt::ISODate);
    pgdata = pgdata.replace("_LINE4_", "Reply timestamp : " + temp);

    reply->setStatusCode(QtHttpReply::Ok);
    QByteArray buffer((const char*)pgdata.toStdString().c_str(), pgdata.toStdString().length());
    reply->appendRawData(buffer);

}
