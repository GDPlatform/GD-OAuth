#pragma once
#include <Geode/Geode.hpp>
#include "../auth/httprequest.hpp"

using namespace geode::prelude;

class AuthSection : public CCLayerColor {
private:
    CCLabelBMFont* m_label = nullptr;
    CCMenuItemFont* m_authBtn = nullptr;

    bool m_isAlive = true; 

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

        this->setTouchEnabled(true);
        this->setKeypadEnabled(true);

        auto winSize = CCDirector::get()->getWinSize();

        m_label = CCLabelBMFont::create("Authentication", "bigFont.fnt");
        m_label->setPosition(winSize / 2 + CCPoint{0, 60});
        m_label->setScale(0.6f);
        this->addChild(m_label);

        auto closeBtn = CCMenuItemFont::create("Close", this, menu_selector(AuthSection::onClose));
        m_authBtn = CCMenuItemFont::create("Generate Auth Code", this, menu_selector(AuthSection::onGenerateCode));

        auto menu = CCMenu::create(m_authBtn, closeBtn, nullptr);
        menu->alignItemsVerticallyWithPadding(20.0f);
        menu->setPosition(winSize / 2 - CCPoint{0, 20});
        this->addChild(menu);

        return true;
    }

    void onExit() override {
        CCLayerColor::onExit();
        m_isAlive = false;
    }

    void onClose(CCObject*) {
        this->removeFromParentAndCleanup(true);
    }

    void onGenerateCode(CCObject*) {
        auto accountManager = GJAccountManager::get();
        auto accountID = accountManager->m_accountID;

        if (accountID <= 0) {
            m_label->setString("Please login to GD first!");
            return;
        }

        m_authBtn->setEnabled(false);
        m_label->setString("Generating...");

        GDAuthAPI::generateVerificationCode(accountID, [this](std::string code) {
            Loader::get()->queueInMainThread([this, code]() {
                if (!m_isAlive) return;

                if (code == "ERR!" || code == "HR_FAILED") {
                    m_label->setString("Request Failed!");
                    m_authBtn->setEnabled(true);
                } else {
                    m_label->setString(("Code: " + code).c_str());
                    this->scheduleOnce(schedule_selector(AuthSection::reactivateButton), 30.0f);
                }
            });
        });
    }

    void reactivateButton(float) {
        if (m_isAlive) m_authBtn->setEnabled(true);
    }

    void keyBackClicked() override {
        onClose(nullptr);
    }
};