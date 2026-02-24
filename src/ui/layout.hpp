#pragma once
#include <Geode/Geode.hpp>
#include "../auth/httprequest.hpp" // Make sure the path is correct

using namespace geode::prelude;

/**
 * GDAuthCodeLayer: Popup that shows the verification code to the user.
 * Inherits from geode::Popup to use the native UI style.
 */
class GDAuthCodeLayer : public geode::Popup<std::string const&> {
protected:
    bool setup(std::string const& code) override {
        this->setTitle("GD-OAuth Authenticator");
        
        // Use the main popup layer's content size
        auto winSize = m_mainLayer->getContentSize();

        // 1. Instruction label
        auto label = CCLabelBMFont::create("Enter this code on the website:", "bigFont.fnt");
        if (label) {
            label->setScale(0.5f);
            label->setPosition(winSize / 2 + ccp(0, 40));
            m_mainLayer->addChild(label);
        }

        // 2. Verification code (highlighted in gold)
        auto codeLabel = CCLabelBMFont::create(code.c_str(), "goldFont.fnt");
        if (codeLabel) {
            codeLabel->setScale(1.1f);
            codeLabel->setPosition(winSize / 2 + ccp(0, 5));
            m_mainLayer->addChild(codeLabel);
        }

        // --- QUALITY OF LIFE: Clipboard ---
        // Automatically copy on open to avoid transcription errors
        utils::clipboard::write(code);
        Notification::create("Code copied", NotificationIcon::Success)->show();

        // 3. Button to open the login URL
        auto webBtnSpr = ButtonSprite::create("Open Web", "goldFont.fnt", "GJ_button_01.png", .8f);
        auto webBtn = CCMenuItemSpriteExtra::create(
            webBtnSpr, this, menu_selector(GDAuthCodeLayer::onOpenWeb)
        );
        
        if (webBtn && m_buttonMenu) {
            webBtn->setPosition(ccp(0, -60));
            m_buttonMenu->addChild(webBtn);
        }

        return true;
    }

public:
    static GDAuthCodeLayer* create(std::string const& code) {
        auto ret = new GDAuthCodeLayer();
        // Define a 240x160 size for the popup
        if (ret && ret->initAnchored(240, 160, code)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    void onOpenWeb(CCObject*) {
        // CCApplication is the most stable way to open URLs on Windows [cite: 5, 6]
        CCApplication::sharedApplication()->openURL("https://gdplatform.netlify.app/login");
    }
};
