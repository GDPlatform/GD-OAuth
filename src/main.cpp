#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "authenticator.hpp"

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto myButton = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png"),
            this,
            menu_selector(MyMenuLayer::onMyButton)
        );

        if (myButton) {
            myButton->setID("gd-oauth-button"_spr);

            auto menu = this->getChildByID("bottom-menu");
            
            if (menu) {
                menu->addChild(myButton);
                menu->updateLayout();
            } 

            else {
                auto fallbackMenu = CCMenu::create();
                fallbackMenu->setPosition({ 40, 40 });
                fallbackMenu->addChild(myButton);
                this->addChild(fallbackMenu, 100);
            }
        }

        return true;
    }

    void onMyButton(CCObject* sender) {
        Authenticator auth;
        auth.startAuthProcess();
    }
};
