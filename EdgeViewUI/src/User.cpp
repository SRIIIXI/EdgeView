#include "User.hpp"

User::User()
{

}

User::User(QString iUserId, QString iFirstName, QString iLastName, QString iEmailId, QString iPhoneNo)
{
    UserId_ = iUserId;
    FirstName_ = iFirstName;
    LastName_ = iLastName;
    EmailId_ = iEmailId;
    PhoneNo_ = iPhoneNo;
}

User::User(const User& other)
{
    UserId_ = other.UserId_;
    FirstName_ = other.FirstName_;
    LastName_ = other.LastName_;
    EmailId_ = other.EmailId_;
    PhoneNo_ = other.PhoneNo_;
}

User& User::operator = (const User& other)
{
    UserId_ = other.UserId_;
    FirstName_ = other.FirstName_;
    LastName_ = other.LastName_;
    EmailId_ = other.EmailId_;
    PhoneNo_ = other.PhoneNo_;
    return *this;
}

User::~User()
{

}
