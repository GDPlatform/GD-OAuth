#pragma once
#include <Geode/Geode.hpp>
#include "auth/httprequest.hpp"
#include "ui/layout.hpp"

using namespace geode::prelude;

class Authenticator
{
public:
    void startAuthProcess()
    {
        // 1. Safe verification of the Manager
        auto GLM = GJAccountManager::sharedState();
        if (!GLM) {
            Notification::create("Internal Error (Manager)", NotificationIcon::Error)->show();
            return;
        }

        int accountID = GLM->m_accountID;

        // 2. Check if a session is logged in
        if (accountID <= 0)
        {
            FLAlertLayer::create(
                "GD-OAuth",
                "Log in to <cg>Geometry Dash</c> to generate a code.",
                "OK")
                ->show();
            return;
        }

        // 3. Immediate visual feedback
        auto statusNotification = Notification::create("Generating code...", NotificationIcon::Loading);
        statusNotification->show();

        // 4. API call (capture by value to avoid scope issues)
        GDAuthAPI::generateVerificationCode(accountID, [](std::string const &code)
        {
            if (code == "Network Error" || code == "ERR!") {
                FLAlertLayer::create("Error", "Failed to connect to GDPlatform.", "OK")->show();
            } else {
                // 5. Safe creation of the UI
                auto popup = GDAuthCodeLayer::create(code);
                if (popup) {
                    popup->show();
                } else {
                    Notification::create("Failed to create popup", NotificationIcon::Error)->show();
                }
            }
        });
    }
};
