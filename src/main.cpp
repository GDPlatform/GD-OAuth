#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "ui/_authsection.hpp"

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() override {
        if (!MenuLayer::init())
            return false;

        auto sprite = CCSprite::create("ic_auth.png"_spr);
        
        if (!sprite) {
            sprite = CCSprite::createWithSpriteFrameName("GJ_downloadsIcon_001.png");
            log::warn("ic_auth.png returned to undefined or null, using fallback.");
        }

        auto myButton = CCMenuItemSpriteExtra::create(
            sprite, 
            this, 
            menu_selector(MyMenuLayer::onMyButton)
        );

        if (sprite) {
            myButton->setScale(0.25f);
        }
        myButton->setID("gd-oauth-button"_spr);

        if (auto menu = this->getChildByID("bottom-menu")) {
            menu->addChild(myButton);

            menu->updateLayout();
        }

        return true;
    }

    void onMyButton(CCObject* sender) {
        auto section = AuthSection::create();
        if (section) {
            CCScene::get()->addChild(section, 100); 
        }
    }
};