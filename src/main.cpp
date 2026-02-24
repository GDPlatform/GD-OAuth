#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "authenticator.hpp"

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer)
{
    bool init()
    {
        if (!MenuLayer::init())
        {
            return false;
        }

        auto sprite = CCSprite::create("ic_auth.png");
        if (!sprite)
        {
            log::error("No se pudo cargar ic_auth.png");
            return true;
        }

        auto myButton = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(MyMenuLayer::onMyButton));

        if (myButton)
        {
            myButton->setID("gd-oauth-button"_spr);

            auto menu = this->getChildByID("bottom-menu");

            if (menu)
            {
                menu->addChild(myButton);
                menu->updateLayout();
            }
            else
            {
                auto fallbackMenu = CCMenu::create();
                fallbackMenu->setPosition({40, 40});
                fallbackMenu->addChild(myButton);
                this->addChild(fallbackMenu, 100);
            }
        }

        return true;
    }

    /**
     * Callback del botón: Llama al proceso de autenticación real.
     */
    void onMyButton(CCObject *sender)
    {
        // Instanciamos el autenticador para iniciar la petición a la API
        Authenticator auth;
        auth.startAuthProcess();
    }
};