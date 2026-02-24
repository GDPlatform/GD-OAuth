#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class AuthSection : public CCLayerColor {
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
        if (!CCLayerColor::initWithColor({0, 0, 0, 180})) {
            return false;
        }

        auto winSize = CCDirector::sharedDirector()->getWinSize();

        auto label = CCLabelBMFont::create("Authentication", "bigFont.fnt");
        label->setPosition(winSize.width / 2, winSize.height - 80);
        this->addChild(label);

        auto closeBtn = CCMenuItemFont::create(
            "Close",
            this,
            menu_selector(AuthSection::onClose)
        );

        auto menu = CCMenu::create(closeBtn, nullptr);
        menu->setPosition(winSize.width / 2, 60);
        this->addChild(menu);

        return true;
    }

    void onClose(CCObject*) {
        this->removeFromParentAndCleanup(true);
    }
};
