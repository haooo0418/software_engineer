#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string password;
    std::string userId;

public:
    User();
    User(const std::string& username, const std::string& password);
    User(const std::string& username, const std::string& password, const std::string& userId);

    // Getters
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getUserId() const;

    // Setters
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setUserId(const std::string& userId);

    // Verification
    bool verifyPassword(const std::string& password) const;

    // Serialization
    std::string serialize() const;
    static User deserialize(const std::string& data);
};

#endif // USER_H
