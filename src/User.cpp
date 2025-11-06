#include "User.h"
#include <sstream>
#include <vector>

User::User() : username(""), password(""), userId("") {}

User::User(const std::string& username, const std::string& password)
    : username(username), password(password), userId("") {}

User::User(const std::string& username, const std::string& password, const std::string& userId)
    : username(username), password(password), userId(userId) {}

std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {
    return password;
}

std::string User::getUserId() const {
    return userId;
}

void User::setUsername(const std::string& username) {
    this->username = username;
}

void User::setPassword(const std::string& password) {
    this->password = password;
}

void User::setUserId(const std::string& userId) {
    this->userId = userId;
}

bool User::verifyPassword(const std::string& password) const {
    return this->password == password;
}

std::string User::serialize() const {
    std::ostringstream oss;
    oss << userId << "|" << username << "|" << password;
    return oss.str();
}

User User::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string userId, username, password;
    
    std::getline(iss, userId, '|');
    std::getline(iss, username, '|');
    std::getline(iss, password, '|');
    
    return User(username, password, userId);
}
