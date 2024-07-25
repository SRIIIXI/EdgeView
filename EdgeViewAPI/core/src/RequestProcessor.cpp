#include "RequestProcessor.h"

RequestProcessor::RequestProcessor(int hashseed, QTextStream *ostream, QObject *parent) : QObject(parent)
{
    _ConsoleOut = ostream;
    _VerboseLog = false;
}

RequestProcessor::RequestProcessor(int hashseed, QSqlDatabase* pdatabase, QString dataDirectory, QTextStream* ostream, QObject *parent) : QObject(parent)
{
    _DataDirectory = dataDirectory;
    _Database = pdatabase;
    _ConsoleOut = ostream;
    _VerboseLog = false;
}

void RequestProcessor::setInterfaces(QSqlDatabase* pdatabase, QString dataDirectory)
{
    _DataDirectory = dataDirectory;
    _Database = pdatabase;
}

RequestProcessor::~RequestProcessor()
{
}

bool RequestProcessor::processSignIn(QString &username, QString &password, QString &userid, QString &utype)
{
    Users usr(_Database, "users");

    QList<QSqlRecord>* reclist = usr.getSelectedRecords("username", username);

    if(reclist->count() < 1)
    {
        return false;
    }

    userid = reclist[0].value(0).value(0).toString();
    QString passwd = reclist[0].value(0).value(8).toString();
    utype = reclist[0].value(0).value(9).toString();

    if(passwd == password)
    {
        return true;
    }

    //Make this userid invalid
    userid = "-1";
    return false;
}

bool RequestProcessor::processSignUp(QMap<QString, QString> &postitems, QString &statusmessage, QString &server)
{
    int errcount = 0;

    QString origpwd = "";
    QString confpwd = "";

    if(postitems.contains("password"))
    {
        origpwd = postitems.value("password");
    }

    if(postitems.contains("confpassword"))
    {
        confpwd = postitems.value("confpassword");
    }

    if(origpwd != confpwd)
    {
        statusmessage += "<tr><td>Entered passwords do not match</tr></td>";
        errcount++;
    }

    QString vertoken = QUuid::createUuid().toString();
    vertoken = vertoken.remove(vertoken.length() -1, 1);
    vertoken = vertoken.remove(0, 1);

    QString verifyurl = server + vertoken;

    QString username = "";

    if(postitems.contains("loginid"))
    {
        username = postitems.value("loginid");
    }

    Users usr(_Database, "users");

    QList<QSqlRecord>* reclist = usr.getSelectedRecords("username", username);

    if(reclist->count() > 0)
    {
        statusmessage += "<tr><td>Username or login id ";
        statusmessage += username;
        statusmessage += " already taken</tr></td>";
        errcount++;
    }

    if(errcount > 0)
    {
        return false;
    }

    uint32_t uid = usr.maximumValue("userid").toUInt();

    uid++;

    QVariant uidstr(uid);

    QString sqlf = "insert into users (userid";
    QString sqlv =  " values(" + uidstr.toString();

    sqlf += ", username";
    sqlv += ", '" + username +"'";

    if(postitems.contains("email"))
    {
        sqlf += ", email";
        sqlv += ", '" + postitems.value("email") +"'";
    }

    if(postitems.contains("password"))
    {
        sqlf += ", password";
        sqlv += ", '" + postitems.value("password") +"'";
    }

    if(postitems.contains("firstname"))
    {
        sqlf += ", firstname";
        sqlv += ", '" + postitems.value("firstname") +"'";
    }

    if(postitems.contains("lastname"))
    {
        sqlf += ", lastname";
        sqlv += ", '" + postitems.value("lastname") +"'";
    }

    if(postitems.contains("company"))
    {
        sqlf += ", company";
        sqlv += ", '" + postitems.value("company") +"'";
    }

    if(postitems.contains("company"))
    {
        sqlf += ", company";
        sqlv += ", '" + postitems.value("company") +"'";
    }

    if(postitems.contains("website"))
    {
        sqlf += ", website";
        sqlv += ", '" + postitems.value("website") +"'";
    }

    if(postitems.contains("addressline1"))
    {
        sqlf += ", addressline1";
        sqlv += ", '" + postitems.value("addressline1") +"'";
    }

    if(postitems.contains("addressline2"))
    {
        sqlf += ", addressline2";
        sqlv += ", '" + postitems.value("addressline2") +"'";
    }

    if(postitems.contains("city"))
    {
        sqlf += ", city";
        sqlv += ", '" + postitems.value("city") +"'";
    }

    if(postitems.contains("state"))
    {
        sqlf += ", state";
        sqlv += ", '" + postitems.value("state") +"'";
    }

    if(postitems.contains("zipcode"))
    {
        sqlf += ", zipcode";
        sqlv += ", '" + postitems.value("zipcode") +"'";
    }

    if(postitems.contains("country"))
    {
        sqlf += ", country";
        sqlv += ", '" + postitems.value("country") +"'";
    }

    if(postitems.contains("description"))
    {
        sqlf += ", description";
        sqlv += ", '" + postitems.value("description") +"'";
    }

    if(postitems.contains("usertype"))
    {
        sqlf += ", usertype";

        if(postitems.value("usertype").toLower() == "administrator")
        {
            sqlv += ", 'X'";
        }
        else
        {
            QString temp = postitems.value("usertype").at(0);
            sqlv += ", '" + temp +"'";
        }
    }

    QString phoneno = postitems.value("phone1", "") + "-" + postitems.value("phone2", "") + "-" + postitems.value("phone3", "");

    sqlf += ", phone";
    sqlv += ", '" + phoneno +"'";

    sqlf += ", verificationtoken";
    sqlv += ", '" + vertoken +"'";

    sqlf += ")";
    sqlv += ")";

    QString sqlstring = sqlf + sqlv;

    try
    {
        _Database->transaction();

        _Database->exec(sqlstring);

        _Database->commit();
    }
    catch(QException e)
    {
       _Database->rollback();

       _Database->lastError().text();

       return true;
    }

    statusmessage = "User " + username + " created, verification email has been sent to " + postitems.value("email");

    //Need to send out the email here

    return true;
}

bool RequestProcessor::processSignUpVerify(QString &token, QString &statusmessage)
{
    Users usr(_Database, "users");

    QList<QSqlRecord>* reclist = usr.getSelectedRecords("verification", token);

    if(reclist->count() < 1)
    {
        statusmessage = "Invalid verification token";
        return false;
    }

    QString sqlstring = "update users set signupverified = 'Y' where userid = " + reclist->at(0).value(0).toString();;

    try
    {
        _Database->transaction();

        _Database->exec(sqlstring);

        _Database->commit();
    }
    catch(QException e)
    {
       _Database->rollback();

       _Database->lastError().text();

       return false;
    }

    statusmessage = "Signup verified";

    return true;
}

bool RequestProcessor::processGetSubmittedAdList(QString &username, QString &adlist)
{
    QString querystring = "select adid, publisher, slogan, description from adslocal where advertiser = '" + username + "'";

    QSqlQuery query = _Database->exec(querystring);

    while(query.next())
    {
        adlist += "\n<tr>";
        adlist += "<td>" + query.record().value(0).toString() + "</td>";
        adlist += "<td>" + query.record().value(1).toString() + "</td>";
        adlist += "<td>" + query.record().value(2).toString() + "</td>";
        adlist += "<td>" + query.record().value(3).toString() + "</td>";
        adlist += "</tr>\n";
    }

    return true;
}

bool RequestProcessor::processGetPendingAdList(QString &username, QString &adlist)
{
    QString querystring = "select adid, advertiser, slogan, description from adslocal where publisher = '" + username + "' and approvalstate= 'N'";

    QSqlQuery query = _Database->exec(querystring);

    while(query.next())
    {
        adlist += "\n<tr>";
        adlist += "<td><a href=\"getad?adid=" + query.record().value(0).toString()  + "\">" + query.record().value(0).toString() + "</a></td>";
        adlist += "<td>" + query.record().value(1).toString() + "</td>";
        adlist += "<td>" + query.record().value(2).toString() + "</td>";
        adlist += "<td>" + query.record().value(3).toString() + "</td>";
        adlist += "</tr>\n";
    }

    return true;
}

bool RequestProcessor::processGetMasterAdList(QString &adlist)
{
    QString querystring = "select adid, slogan, height, width, price from ads";

    QSqlQuery query = _Database->exec(querystring);

    while(query.next())
    {
        adlist += "\n<tr>";
        adlist += "<td><a href=\"bidforad?adid=" + query.record().value(0).toString()  + "&login_id=_LOGIN_ID_\">" + query.record().value(0).toString() + "</a></td>";
        adlist += "<td>" + query.record().value(1).toString() + "</td>";
        adlist += "<td>" + query.record().value(2).toString() + "</td>";
        adlist += "<td>" + query.record().value(3).toString() + "</td>";
        adlist += "<td>" + query.record().value(4).toString() + "</td>";
        adlist += "</tr>\n";
    }

    return true;
}

bool RequestProcessor::processGetAd(QString &adid, QString &addetails)
{
    Users usr(_Database, "adslocal");

    QList<QSqlRecord>* reclist = usr.getSelectedRecords("adid", adid);

    if(reclist->count() < 1)
    {
        return false;
    }

    QSqlRecord rec = reclist->first();

    QString adtype = rec.value(8).toString();

    if(adtype == "R")
    {
        adtype = "Rotator";
    }
    else
    {
        adtype = "Exclusive";
    }

    addetails = addetails.replace("_TYPE_", adtype);

    addetails = addetails.replace("_PRICE_", rec.value(3).toString());
    addetails = addetails.replace("_DAYS_", rec.value(10).toString());
    addetails = addetails.replace("_START_TIME_", rec.value(11).toString());
    addetails = addetails.replace("_WIDTH_", rec.value(5).toString());
    addetails = addetails.replace("_HEIGHT_", rec.value(6).toString());
    addetails = addetails.replace("_WEB_SITE_", rec.value(1).toString());
    addetails = addetails.replace("_SLOGAN_", rec.value(7).toString());
    addetails = addetails.replace("_DESCRIPTION_", rec.value(9).toString());

    return true;
}

bool RequestProcessor::processGetMasterAd(QString &adid, QString &addetails)
{
    Users usr(_Database, "ads");

    QList<QSqlRecord>* reclist = usr.getSelectedRecords("adid", adid);

    if(reclist->count() < 1)
    {
        return false;
    }

    QSqlRecord rec = reclist->first();

    QDateTime dt = rec.value(12).toDateTime();

    QString str = rec.value(12).toString();

    QString adtype = rec.value(9).toString();

    if(adtype == "R")
    {
        adtype = "Rotator";
    }
    else
    {
        adtype = "Exclusive";
    }

    addetails = addetails.replace("_TYPE_", adtype);

    addetails = addetails.replace("_AD_ID_", rec.value(0).toString());
    addetails = addetails.replace("_PUBLISHER_", rec.value(1).toString());

    QStringList pricestr = rec.value(4).toString().split('.');

    if(pricestr.count() < 1)
    {
        pricestr.append("0");
    }

    if(pricestr.count() < 2)
    {
        pricestr.append("0");
    }

    addetails = addetails.replace("_PRICE_DOLLARS_", pricestr[0]);
    addetails = addetails.replace("_PRICE_CENTS_", pricestr[1]);

    addetails = addetails.replace("_DAYS_", rec.value(11).toString());
    addetails = addetails.replace("_WIDTH_", rec.value(6).toString());
    addetails = addetails.replace("_HEIGHT_", rec.value(7).toString());
    addetails = addetails.replace("_WEB_SITE_", rec.value(2).toString());
    addetails = addetails.replace("_SLOGAN_", rec.value(8).toString());
    addetails = addetails.replace("_DESCRIPTION_", rec.value(3).toString());

    addetails = addetails.replace("_MM_", QVariant(dt.date().month()).toString());
    addetails = addetails.replace("_DD_", QVariant(dt.date().day()).toString());
    addetails = addetails.replace("_YYYY_", QVariant(dt.date().year()).toString());
    addetails = addetails.replace("_HH_", QVariant(dt.time().hour()).toString());
    addetails = addetails.replace("_MN_", QVariant(dt.time().minute()).toString());
    addetails = addetails.replace("_SS_", QVariant(dt.time().second()).toString());
    return true;
}

bool RequestProcessor::processCreateAd(QMap<QString, QString> &postitems, QString &publisher, QString &statusmessage)
{
    Ads ads(_Database, "ads");

    uint32_t adid = ads.maximumValue("adid").toUInt();

    adid++;

    QVariant adidstr(adid);

    QString sqlf = "insert into ads (adid";
    QString sqlv =  " values(" + adidstr.toString();

    if(publisher.length() < 1)
    {
        if(postitems.contains("login_id"))
        {
            publisher = postitems.value("login_id");
        }
    }

    sqlf += ", publisher";
    sqlv += ", '" + publisher +"'";

    sqlf += ", approvalstate";
    sqlv += ", 'N'";

    if(postitems.contains("notes"))
    {
        sqlf += ", description";
        sqlv += ", '" + postitems.value("notes") +"'";
        sqlf += ", notes";
        sqlv += ", '" + postitems.value("notes") +"'";
    }

    if(postitems.contains("website"))
    {
        sqlf += ", url";
        QString webs = postitems.value("website");
        webs = webs.replace("%3A", ":");
        webs = webs.replace("%2F", "/");
        sqlv += ", '" + webs +"'";
    }

    if(postitems.contains("slogan"))
    {
        sqlf += ", slogan";
        sqlv += ", '" + postitems.value("slogan") +"'";
    }

    if(postitems.contains("daystorun"))
    {
        sqlf += ", daystorun";
        sqlv += ", " + postitems.value("daystorun");
    }

    if(postitems.contains("price_dollars") && postitems.contains("price_cents"))
    {
        sqlf += ", price";
        sqlv += ", " + postitems.value("price_dollars") + "." + postitems.value("price_cents");
    }

    if(postitems.contains("adtype"))
    {
        QChar ch = postitems.value("adtype").toUpper().at(0);
        sqlf += ", adtype";
        sqlv += ", '";
        sqlv += ch;
        sqlv += "'";
    }

    QString tstamp = postitems.value("year") + "-" + postitems.value("month") + "-" + postitems.value("day") + " " + postitems.value("hour") + ":" + postitems.value("minute") + ":" + postitems.value("second");

    sqlf += ", starttimestamp";
    sqlv += ", '" + tstamp +"'";

    QString extension = "jpg";

    if(postitems.contains("extension"))
    {
        extension = postitems.value("extension");
    }

    QString cachefile = _DataDirectory + "/cache/" + publisher + "." + extension;

    QImage px(cachefile);
    QString height = QVariant(px.width()).toString();
    QString width = QVariant(px.height()).toString();

    sqlf += ", width";
    sqlv += ", " + height;

    sqlf += ", height";
    sqlv += ", " + width;

    sqlf += ")";
    sqlv += ")";

    QString sqlstring = sqlf + sqlv;

    try
    {
        _Database->transaction();

        _Database->exec(sqlstring);

        _Database->commit();

        //Now copy the file from the cache
        QString fname = _DataDirectory + "/ads/" + adidstr.toString() + "." + extension;

        QFile nfl(fname);

        if(nfl.exists())
        {
            nfl.remove();
        }

        QFile fl(cachefile);
        fl.copy(fname);
        fl.remove(cachefile);
    }
    catch(QException e)
    {
       _Database->rollback();

       _Database->lastError().text();

       statusmessage = "Could not create ad";

       return false;
    }

    statusmessage = "Ad created";

    return true;
}

bool RequestProcessor::processBidForAd(QMap<QString, QString> &postitems, QString &statusmessage)
{
    QString advertiser = "";

    AdsLocal ads(_Database, "adslocal");

    uint32_t adid = ads.maximumValue("adid").toUInt();

    adid++;

    QVariant adidstr(adid);

    QString sqlf = "insert into adslocal (";
    QString sqlv =  " values(";

    sqlf += " adid";
    sqlv += adidstr.toString();

    if(postitems.contains("publisher"))
    {
        sqlf += ", publisher";
        sqlv += ", '" + postitems.value("publisher") +"'";
    }

    if(postitems.contains("advertiser"))
    {
        sqlf += ", advertiser";
        advertiser = postitems.value("advertiser");
        sqlv += ", '" + postitems.value("advertiser") +"'";
    }

    sqlf += ", approvalstate";
    sqlv += ", 'N'";

    if(postitems.contains("notes"))
    {
        sqlf += ", description";
        sqlv += ", '" + postitems.value("notes") +"'";
        sqlf += ", notes";
        sqlv += ", '" + postitems.value("notes") +"'";
    }

    if(postitems.contains("website"))
    {
        sqlf += ", url";
        QString webs = postitems.value("website");
        webs = webs.replace("%3A", ":");
        webs = webs.replace("%2F", "/");
        sqlv += ", '" + webs +"'";
    }

    if(postitems.contains("slogan"))
    {
        sqlf += ", slogan";
        sqlv += ", '" + postitems.value("slogan") +"'";
    }

    if(postitems.contains("daystorun"))
    {
        sqlf += ", daystorun";
        sqlv += ", " + postitems.value("daystorun");
    }

    if(postitems.contains("price_dollars") && postitems.contains("price_cents"))
    {
        sqlf += ", price";
        sqlv += ", " + postitems.value("price_dollars") + "." + postitems.value("price_cents");
    }

    if(postitems.contains("adtype"))
    {
        QChar ch = postitems.value("adtype").toUpper().at(0);
        sqlf += ", adtype";
        sqlv += ", '";
        sqlv += ch;
        sqlv += "'";
    }

    QString tstamp = postitems.value("year") + "-" + postitems.value("month") + "-" + postitems.value("day") + " " + postitems.value("hour") + ":" + postitems.value("minute") + ":" + postitems.value("second");

    sqlf += ", starttimestamp";
    sqlv += ", '" + tstamp +"'";

    QString extension = "jpg";

    if(postitems.contains("extension"))
    {
        extension = postitems.value("extension");
    }

    QString cachefile = _DataDirectory + "/cache/" + advertiser + "." + extension;

    QImage px(cachefile);
    QString height = QVariant(px.width()).toString();
    QString width = QVariant(px.height()).toString();

    sqlf += ", width";
    sqlv += ", " + height;

    sqlf += ", height";
    sqlv += ", " + width;


    sqlf += ")";
    sqlv += ")";

    QString sqlstring = sqlf + sqlv;

    try
    {
        _Database->transaction();

        _Database->exec(sqlstring);

        _Database->commit();

        //Now copy the file from the cache
        QString fname = _DataDirectory + "/adslocal/" + adidstr.toString() + "." + extension;

        QFile nfl(fname);

        if(nfl.exists())
        {
            nfl.remove();
        }

        QFile fl(cachefile);
        fl.copy(fname);
        fl.remove(cachefile);
    }
    catch(QException e)
    {
       _Database->rollback();

       _Database->lastError().text();

       statusmessage = "Could not place bid for the ad";

       return false;
    }

    statusmessage = "Ad bid placed";

    return true;
}

bool RequestProcessor::processSetAdPrice(QString &adid, QString &price, QString &statusmessage)
{
    QString sqlstring = "update ads set price = _price_";

    sqlstring = sqlstring.replace("_price_", price);

    try
    {
        _Database->transaction();

        _Database->exec(sqlstring);

        _Database->commit();
    }
    catch(QException e)
    {
       _Database->rollback();

       _Database->lastError().text();

       return false;
    }

    statusmessage = "Ad approved";

    return true;
}


bool RequestProcessor::processApproveAd(QString &adid, QString &apprflag, QString &apprtext, QString &statusmessage)
{
    QString sqlstring = "update adslocal set approvalstate = '_approvalflag_', notes = '_notes_' where adid = _adid_";

    sqlstring = sqlstring.replace("_approvalflag_", apprflag);
    sqlstring = sqlstring.replace("_notes_", apprtext);
    sqlstring = sqlstring.replace("_adid_", adid);

    try
    {
        _Database->transaction();

        _Database->exec(sqlstring);

        _Database->commit();
    }
    catch(QException e)
    {
       _Database->rollback();

       _Database->lastError().text();

       return false;
    }

    statusmessage = "Ad approved";

    return true;
}

bool RequestProcessor::processUpdateBanner(QString &adid, QByteArray &imagedata, QString &ftype, QString &statusmessage)
{
    QDir dir(_DataDirectory+"/ads/");

    QFileInfoList flist = dir.entryInfoList();

    int fcount = flist.count();

    for(int idx = 0;  idx < fcount; idx++)
    {
        QFileInfo finfo = flist.at(idx);

        if(finfo.baseName() == adid)
        {
            QFile file(finfo.filePath());

            if(QFileInfo::exists(finfo.filePath()))
            {
                file.remove();
            }
        }
    }

    QString imagepath = _DataDirectory + "/ads/" + adid + "." + ftype.toLower();

    QFile file(imagepath);

    file.open(QIODevice::WriteOnly);
    file.write(imagedata);
    file.flush();
    file.close();

    statusmessage = "Bannner updated";

    return false;
}

bool RequestProcessor::processGetBanner(QString &fname, QByteArray &imagedata)
{
    QString fpath = _DataDirectory+"/ads/"+fname;

    QFile file(fpath);

    if(file.open(QIODevice::ReadOnly))
    {
        imagedata = file.readAll();
        return true;
    }
    return false;
}

void RequestProcessor::enableVerboseLog()
{
    _VerboseLog = true;
}
