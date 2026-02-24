#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "authenticator.hpp"
#include "ui/_authsection.hpp"

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer)
{
    bool init() override
    {
        if (!MenuLayer::init())
            return false;

        auto sprite = CCSprite::create((Mod::get()->getResourcesDir() / "ic_auth.png").string().c_str());
        if (!sprite)
        {
            log::error("ic_auth.png (404)");
            return true;
        }

        sprite->setScale(0.5f);

        auto myButton = CCMenuItemSpriteExtra::create(sprite, this, menu_selector(MyMenuLayer::onMyButton));
        if (!myButton)
            return true;

        myButton->setID("gd-oauth-button"_spr);

        auto menu = this->getChildByID("bottom-menu");
        if (!menu)
        {
            menu = CCMenu::create();
            menu->setPosition({40, 40});
            this->addChild(menu, 100);
        }

        menu->addChild(myButton);
        menu->updateLayout();

        return true;
    }

    void onMyButton(CCObject *sender)
    {
        auto section = AuthSection::create();
        if (!section)
            return;

        section->setTouchEnabled(true);

        auto runningScene = CCDirector::sharedDirector()->getRunningScene();
        if (runningScene)
        {
            runningScene->addChild(section, 1000);
        }
    }
};
