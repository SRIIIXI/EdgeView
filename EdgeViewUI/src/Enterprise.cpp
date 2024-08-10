#include "Enterprise.hpp"

Enterprise::Enterprise()
{

}

Enterprise::Enterprise(QString iEnterpriseId, QString iContactFirstName, QString iContactLastName, QString iContactEmailId, QString iContactPhoneNo)
{
    EnterpriseId_ = iEnterpriseId;
    ContactFirstName_ = iContactFirstName;
    ContactLastName_ = iContactLastName;
    ContactEmailId_ = iContactEmailId;
    ContactPhoneNo_ = iContactPhoneNo;
}

Enterprise::Enterprise(const Enterprise& other)
{
    EnterpriseId_ = other.EnterpriseId_;
    ContactFirstName_ = other.ContactFirstName_;
    ContactLastName_ = other.ContactLastName_;
    ContactEmailId_ = other.ContactEmailId_;
    ContactPhoneNo_ = other.ContactPhoneNo_;
}

Enterprise& Enterprise::operator = (const Enterprise& other)
{
    EnterpriseId_ = other.EnterpriseId_;
    ContactFirstName_ = other.ContactFirstName_;
    ContactLastName_ = other.ContactLastName_;
    ContactEmailId_ = other.ContactEmailId_;
    ContactPhoneNo_ = other.ContactPhoneNo_;
    return *this;
}

Enterprise::~Enterprise()
{

}
