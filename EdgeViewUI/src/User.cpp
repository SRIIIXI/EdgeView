#include "User.hpp"

User::User()
{

}

User::User(QString iUserId, QString iFirstName, QString iLastName, QString iEmailId, QString iContactNo)
{
    UserId_ = iUserId;
    FirstName_ = iFirstName;
    LastName_ = iLastName;
    EmailId_ = iEmailId;
    ContactNo_ = iContactNo;
}

User::User(const User& other)
{
    UserId_ = other.UserId_;
    FirstName_ = other.FirstName_;
    LastName_ = other.LastName_;
    EmailId_ = other.EmailId_;
    ContactNo_ = other.ContactNo_;
}

User& User::operator = (const User& other)
{
    UserId_ = other.UserId_;
    FirstName_ = other.FirstName_;
    LastName_ = other.LastName_;
    EmailId_ = other.EmailId_;
    ContactNo_ = other.ContactNo_;
    return *this;
}

User::~User()
{

}
