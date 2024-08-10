#ifndef ENTERPRISE_
#define ENTERPRISE_

#include <QtCore>

class Enterprise
{
public:
    Q_GADGET

public:
    QString EnterpriseId_;
public:
    QString ContactFirstName_;
public:
    QString  ContactLastName_;
public:
    QString  ContactEmailId_;
public:
    QString  ContactPhoneNo_;
public:
    Q_PROPERTY(QString EnterpriseId MEMBER EnterpriseId_)
    Q_PROPERTY(QString ContactFirstName MEMBER ContactFirstName_)
    Q_PROPERTY(QString ContactLastName MEMBER ContactLastName_)
    Q_PROPERTY(QString ContactEmailId MEMBER ContactEmailId_)
    Q_PROPERTY(QString ContactPhoneNo MEMBER ContactPhoneNo_)

public:
    Enterprise();
    Enterprise(QString iEnterpriseId, QString iContactFirstName, QString  iContactLastName, QString  iContactEmailId, QString  iContactPhoneNo);
    Enterprise(const Enterprise& other);
    Enterprise& operator = (const Enterprise& other);
    ~Enterprise();
};


#endif
