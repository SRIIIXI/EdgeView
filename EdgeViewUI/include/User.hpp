#ifndef USER_
#define USER_

#include <QtCore>

class User
{
public:
    Q_GADGET

public:
    QString UserId_;
public:
    QString FirstName_;
public:
    QString  LastName_;
public:
    QString  EmailId_;
public:
    QString  PhoneNo_;
public:
    Q_PROPERTY(QString UserId MEMBER UserId_)
    Q_PROPERTY(QString FirstName MEMBER FirstName_)
    Q_PROPERTY(QString LastName MEMBER LastName_)
    Q_PROPERTY(QString EmailId MEMBER EmailId_)
    Q_PROPERTY(QString PhoneNo MEMBER PhoneNo_)

public:
    User();
    User(QString iUserId, QString iFirstName, QString  iLastName, QString  iEmailId, QString  iPhoneNo);
    User(const User& other);
    User& operator = (const User& other);
    ~User();
};


#endif
