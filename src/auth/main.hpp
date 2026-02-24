#pragma once
#include <string>

struct GDUserSession {
    int accountID;
    std::string email;
    std::string sessionToken;
    bool isAuthenticated = false;
};

class AuthManager {
public:
    static AuthManager& get() {
        static AuthManager instance;
        return instance;
    }
    GDUserSession currentSession;
};