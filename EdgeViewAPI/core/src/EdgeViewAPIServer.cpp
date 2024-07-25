#include "AdBuyServer.h"

EdgeViewAPIServer::EdgeViewAPIServer(int argc, char *argv[]) : QCoreApplication (argc, argv)
{
    _Port = 8080;
    _ConsoleOut = new QTextStream(stdout);
    _VerboseLog = false;
    _ServerName = "AdBuy Server";
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
    *_ConsoleOut << "AdBuyHere Server v1.0" << Qt::endl;

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

    if(url.contains("masteradlist"))
    {
        getMasterAdList(request, reply);
        return;
    }

    if(url.contains("getad"))
    {
        if(request->getCommand() == "POST")
        {
            approveAd(postitems, request, reply);
        }
        else
        {
            getAd(request, reply);
        }
        return;
    }

    if(url.contains("approvead"))
    {
        approveAd(postitems, request, reply);
        return;
    }

    if(url.contains("/createad") || url.contains("form_create_ad"))
    {
        if(request->getCommand() == "GET")
        {
            getCreateAdPage(request, reply);
        }

        if(request->getCommand() == "POST")
        {
            createAd(postitems, request, reply);
        }

        return;
    }

    if(url.contains("/bidforad"))
    {
        if(request->getCommand() == "GET")
        {
            buyAd(request, reply);
        }

        if(request->getCommand() == "POST")
        {
            bidForAd(postitems, request, reply);
        }

        return;
    }

    if(url.contains("/pendingadlist"))
    {
        QString qry = request->getUrl().query();
        QString username = request->getClient()->getUserName();

        if(username.length() < 1)
        {
            username = qry.replace("login_id=", "");
        }

        getPendingAdList(reply, username);
        return;
    }

    if(url.contains("/submittedadlist"))
    {
        QString qry = request->getUrl().query();
        QString username = request->getClient()->getUserName();

        if(username.length() < 1)
        {
            username = qry.replace("login_id=", "");
        }

        getSubmittedAdList(reply, username);
        return;
    }

    if(url.contains("/setbanner"))
    {
        setBanner(request, reply);
        return;
    }

    if(url.contains("/signupverify"))
    {
        signUpVerify(request, reply);
        return;
    }

    if(url.contains("/getbanner"))
    {
        getBanner(request, reply);
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
        if(usertype == "A")
        {
            getSubmittedAdList(reply, loginid);
        }

        if(usertype == "P")
        {
            getPendingAdList(reply, loginid);
        }

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

void EdgeViewAPIServer::getPendingAdList(QtHttpReply *reply, QString &username)
{
    QString data;
    _RequestProcessor->processGetPendingAdList(username, data);

    QString pgdata = "";

    getTemplatePage("form_adlocallist_publisher.html", pgdata);

    pgdata = pgdata.replace("_AD_LIST_TYPE_PLACE_HOLEDER_", "Pending Ad List");
    pgdata = pgdata.replace("_USER_NAME_", username);
    pgdata = pgdata.replace("_USER_TYPE_", "Advertiser");
    pgdata = pgdata.replace("<!--_ROW_PLACE_HOLDER_-->", data);

    reply->setStatusCode(QtHttpReply::Ok);
    QByteArray buffer((const char*)pgdata.toStdString().c_str(), pgdata.toStdString().length());
    reply->appendRawData(buffer);
}

void EdgeViewAPIServer::getSubmittedAdList(QtHttpReply *reply, QString &username)
{
    QString data;
    _RequestProcessor->processGetSubmittedAdList(username, data);

    QString pgdata = "";

    getTemplatePage("form_adlocallist_advertiser.html", pgdata);

    pgdata = pgdata.replace("_AD_LIST_TYPE_PLACE_HOLEDER_", "Submitted Ad List");
    pgdata = pgdata.replace("_USER_NAME_", username);
    pgdata = pgdata.replace("_USER_TYPE_", "Publisher");
    pgdata = pgdata.replace("<!--_ROW_PLACE_HOLDER_-->", data);

    reply->setStatusCode(QtHttpReply::Ok);
    QByteArray buffer((const char*)pgdata.toStdString().c_str(), pgdata.toStdString().length());
    reply->appendRawData(buffer);
}

void EdgeViewAPIServer::getMasterAdList(QtHttpRequest *request, QtHttpReply *reply)
{
    QString username = request->getClient()->getUserName();

    if(username.length() < 1)
    {
        QStringList queries = request->getUrl().query().split('&');
        QString temp = queries[0];
        username = temp.replace("login_id=", "");
    }

    QString data;
    _RequestProcessor->processGetMasterAdList(data);

    QString pgdata = "";

    getTemplatePage("form_adlist.html", pgdata);

    pgdata = pgdata.replace("_AD_LIST_TYPE_PLACE_HOLEDER_", "Master Ad List");
    pgdata = pgdata.replace("<!--_ROW_PLACE_HOLDER_-->", data);
    pgdata = pgdata.replace("_LOGIN_ID_", username);

    reply->setStatusCode(QtHttpReply::Ok);
    QByteArray buffer((const char*)pgdata.toStdString().c_str(), pgdata.toStdString().length());
    reply->appendRawData(buffer);
}

void EdgeViewAPIServer::getCreateAdPage(QtHttpRequest *request, QtHttpReply *reply)
{
    QString url = request->getUrl().toString();

    QString username = url.replace("/createad&login_id=", "");

    QString pgdata = "";

    getTemplatePage("form_create_ad.html", pgdata);

    //pgdata = pgdata.replace("_BANNER_POST_SERVER_URL_", "http://" +  _Host + ":" + QVariant(_Port).toString() + "/setbanner&login_id=" + username);
    pgdata = pgdata.replace("_BANNER_POST_SERVER_URL_", "./setbanner?login_id=" + username);
    pgdata = pgdata.replace("_USER_NAME_", username);

    reply->setStatusCode(QtHttpReply::Ok);
    QByteArray buffer((const char*)pgdata.toStdString().c_str(), pgdata.toStdString().length());
    reply->appendRawData(buffer);
}

void EdgeViewAPIServer::getAd(QtHttpRequest *request, QtHttpReply *reply)
{
    QString url = request->getUrl().toString();

    if(!url.contains("/getad?adid="))
    {
        reply->setStatusCode(QtHttpReply::BadRequest);
        return;
    }

    QString adid = url.replace("/getad?adid=", "");

    QString bannerfile = "http://" + request->getHeader (QtHttpHeader::Host) + "/ads/" + adid+".jpg";

    QString pgdata = "";

    getTemplatePage("form_approve_ad.html", pgdata);

    pgdata = pgdata.replace("_USER_NAME_", request->getClient()->getUserName());

    _RequestProcessor->processGetAd(adid, pgdata);

    pgdata = pgdata.replace("_BANNER_FILE_", bannerfile);
    pgdata = pgdata.replace("_LOGIN_ID_", request->getClient()->getUserName());
    pgdata = pgdata.replace("_AD_ID_", adid);

    QByteArray buffer((const char*)pgdata.toStdString().c_str(), pgdata.toStdString().length());
    reply->appendRawData(buffer);
}

void EdgeViewAPIServer::createAd(QMap<QString, QString> &postitems, QtHttpRequest *request, QtHttpReply *reply)
{
    QString username = request->getClient()->getUserName();
    QString statusmessage = "";

    _RequestProcessor->processCreateAd(postitems, username, statusmessage);

    QString pgdata = "";

    getTemplatePage("form_create_ad_result.html", pgdata);
    pgdata = pgdata.replace("_RESULT_", statusmessage);
    pgdata = pgdata.replace("_USER_NAME_", username);
    QByteArray buffer((const char*)pgdata.toStdString().c_str(), pgdata.toStdString().length());
    reply->appendRawData(buffer);
}

void EdgeViewAPIServer::buyAd(QtHttpRequest *request, QtHttpReply *reply)
{
    QString temp = "";
    QStringList queries = request->getUrl().query().split('&');
    temp = queries[0];
    QString adid = temp.replace("adid=", "");
    temp = queries[1];
    QString username = temp.replace("login_id=", "");

    QString bannerfile = "http://" + request->getHeader (QtHttpHeader::Host) + "/ads/" + adid+".jpg";

    QString pgdata = "";
    getTemplatePage("form_bid_ad.html", pgdata);

    pgdata = pgdata.replace("_BANNER_FILE_", bannerfile);
    pgdata = pgdata.replace("_LOGIN_ID_", username);
    pgdata = pgdata.replace("_ADVERTISER_", username);
    pgdata = pgdata.replace("_HYPER_LINK_", "http://"+_Host + ":" + QVariant(_Port).toString() + "/adid="+adid);
    pgdata = pgdata.replace("_BANNER_POST_SERVER_URL_", "./setbanner?login_id=" + username);

    _RequestProcessor->processGetMasterAd(adid, pgdata);

    QByteArray buffer((const char*)pgdata.toStdString().c_str(), pgdata.toStdString().length());
    reply->appendRawData(buffer);
}

void EdgeViewAPIServer::bidForAd(QMap<QString, QString> &postitems, QtHttpRequest *request, QtHttpReply *reply)
{
    QString username = request->getClient()->getUserName();

    if(username.length() < 1)
    {
        username = postitems.value("advertiser");
    }

    QString statusmessage = "";
    _RequestProcessor->processBidForAd(postitems, statusmessage);

    QString pgdata = "";

    getTemplatePage("form_bid_ad_result.html", pgdata);
    pgdata = pgdata.replace("_RESULT_", statusmessage);
    pgdata = pgdata.replace("_USER_NAME_", username);

    QByteArray buffer((const char*)pgdata.toStdString().c_str(), pgdata.toStdString().length());
    reply->appendRawData(buffer);
}

void EdgeViewAPIServer::approveAd(QMap<QString, QString> &postitems, QtHttpRequest *request, QtHttpReply *reply)
{
    QString url = request->getUrl().path();
    QString apprtext = "";
    QString apprflag = "";
    QString username = "";
    QString adid = "";
    QString statusmessage = "";

    if(postitems.contains("approvalstate"))
    {
        apprtext = postitems.value("approvalstate");
    }

    if(postitems.contains("login_id"))
    {
        username = postitems.value("login_id");
    }

    if(postitems.contains("adid_id"))
    {
        adid = postitems.value("adid_id");
    }

    if(apprtext.toLower() == "approved")
    {
        apprflag = "Y";
    }
    else
    {
        apprflag = "N";
    }

    _RequestProcessor->processApproveAd(adid, apprflag, apprtext, statusmessage);
    getPendingAdList(reply, username);
}

void EdgeViewAPIServer::setAdPrice(QtHttpRequest *request, QtHttpReply *reply)
{
    //QString data = QTextCodec::codecForMib(106)->toUnicode(request->getRawData());
    QString data = request->getRawData().toStdString().c_str();
    QStringList fields = data.split('\n', Qt::SkipEmptyParts, Qt::CaseSensitive);

    if(fields.count() < 4)
    {
        reply->setStatusCode(QtHttpReply::BadRequest);
        return;
    }

    QString username = fields.value(0);
    QString adid = fields.value(1);
    QString price = fields.value(2);
    QString statusmessage = "";

    _RequestProcessor->processSetAdPrice(adid, price, statusmessage);
    QByteArray buffer((const char*)statusmessage.toStdString().c_str(), statusmessage.toStdString().length());
    reply->appendRawData(buffer);
}

void EdgeViewAPIServer::setBanner(QtHttpRequest *request, QtHttpReply *reply)
{   
    QByteArray data = request->getRawData();

    QString extension = "jpg";

    if(request->getHeadersList().contains("Content-Type"))
    {
        extension = request->getHeader("Content-Type");
        extension = extension.replace("image/", "");
    }

    QString query = request->getUrl().query();

    QString username = query.replace("login_id=", "");

    QString cachefile = _DataDirectory + "/cache/" + username + "." + extension;

    QFile fl(cachefile);
    fl.open(QIODevice::WriteOnly);
    fl.write(request->getRawData());
    fl.flush();
    fl.close();

    QImage px(cachefile);
    QString height = QVariant(px.width()).toString();
    QString width = QVariant(px.height()).toString();

    QString statusmessage = width+"x"+height;

    QByteArray buffer((const char*)statusmessage.toStdString().c_str(), statusmessage.toStdString().length());
    reply->appendRawData(buffer);
}

void EdgeViewAPIServer::getBanner(QtHttpRequest *request, QtHttpReply *reply)
{
    QString url = request->getUrl().toString();

    if(!url.contains("/getbanner?fname="))
    {
        reply->setStatusCode(QtHttpReply::BadRequest);
        return;
    }

    QString filename = url.replace("/getbanner?fname=", "");

    QByteArray imagedata;
    _RequestProcessor->processGetBanner(filename, imagedata);
    reply->appendRawData(imagedata);
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

    pgdata = pgdata.replace("_HEADING_", "AdBuyHere : Administrator Login");
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
