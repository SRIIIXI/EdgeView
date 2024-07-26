#include "RequestProcessor.hpp"

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

void RequestProcessor::enableVerboseLog()
{
    _VerboseLog = true;
}
