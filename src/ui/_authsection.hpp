#pragma once
#include <Geode/Geode.hpp>
#include "../auth/httprequest.hpp"

using namespace geode::prelude;

class AuthSection : public CCLayerColor {
private:
    CCLabelBMFont* m_label = nullptr;
    CCMenuItemFont* m_authBtn = nullptr;

public:
    static AuthSection* create() {
        auto ret = new AuthSection();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    bool init() override {
        if (!CCLayerColor::initWithColor({0, 0, 0, 180}))
            return false;

        auto winSize = CCDirector::sharedDirector()->getWinSize();

        m_label = CCLabelBMFont::create("Authentication", "bigFont.fnt");
        m_label->setPosition(winSize.width / 2, winSize.height - 80);
        this->addChild(m_label, 1000);

        auto closeBtn = CCMenuItemFont::create("Close", this, menu_selector(AuthSection::onClose));
        m_authBtn = CCMenuItemFont::create("Generate Auth Code", this, menu_selector(AuthSection::onGenerateCode));

        auto menu = CCMenu::create(closeBtn, m_authBtn, nullptr);
        menu->alignItemsVerticallyWithPadding(20.0f);
        menu->setPosition(winSize.width / 2, winSize.height / 2);
        this->addChild(menu, 1000);

        return true;
    }

    void onClose(CCObject*) {
        this->removeFromParentAndCleanup(true);
    }

    void onGenerateCode(CCObject*) {
        if (!m_authBtn->isEnabled())
            return;

        m_authBtn->setEnabled(false);

        auto accountManager = GJAccountManager::sharedState();
        if (accountManager) {
            auto accountID = accountManager->m_accountID;
            if (accountID > 0) {
                GDAuthAPI::generateVerificationCode(accountID, [this](std::string code){
                    m_label->setString(("Your Auth Code: " + code).c_str());
                });
            } else {
                m_label->setString("No logged-in GD account!");
            }
        } else {
            m_label->setString("Account manager unavailable!");
        }

        this->scheduleOnce(schedule_selector(AuthSection::reactivateButton), 60.0f);
    }

    void reactivateButton(float) {
        m_authBtn->setEnabled(true);
    }
};
