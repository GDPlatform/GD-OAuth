#pragma once
#include <Geode/Geode.hpp>
#include "../auth/httprequest.hpp"

using namespace geode::prelude;

class GDAuthCodeLayer : public geode::Popup<std::string const&> {
protected:
    bool setup(std::string const& code) override {
        this->setTitle("GD-OAuth Authenticator");

        auto winSize = m_mainLayer->getContentSize();

        auto label = CCLabelBMFont::create("Enter this code on the website:", "bigFont.fnt");
        if (label) {
            label->setScale(0.5f);
            label->setPosition(winSize / 2 + ccp(0, 40));
            m_mainLayer->addChild(label);
        }

        auto codeLabel = CCLabelBMFont::create(code.c_str(), "goldFont.fnt");
        if (codeLabel) {
            codeLabel->setScale(1.1f);
            codeLabel->setPosition(winSize / 2 + ccp(0, 5));
            m_mainLayer->addChild(codeLabel);
        }

        utils::clipboard::write(code);
        Notification::create("Code copied", NotificationIcon::Success)->show();

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
        if (ret && ret->initAnchored(240, 160, code)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    void onOpenWeb(CCObject*) {
        CCApplication::sharedApplication()->openURL("https://gdplatform.netlify.app/login");
    }
};
