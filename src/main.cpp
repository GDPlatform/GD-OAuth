#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "authenticator.hpp" // Cambiado para manejar la lógica de red

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        // 1. Crear el botón con el sprite de 'like'
        auto myButton = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png"),
            this,
            menu_selector(MyMenuLayer::onMyButton)
        );

        if (myButton) {
            myButton->setID("gd-oauth-button"_spr);

            // 2. BÚSQUEDA SEGURA DEL MENÚ (Prevención de Crash)
            // Se verifica si el menú existe para evitar el error de puntero nulo (0x0) 
            auto menu = this->getChildByID("bottom-menu");
            
            if (menu) {
                menu->addChild(myButton);
                menu->updateLayout();
            } 
            // 3. FALLBACK: Si otros mods (como Globed o BetterEdit) alteraron el menú [cite: 7, 8]
            else {
                auto fallbackMenu = CCMenu::create();
                fallbackMenu->setPosition({ 40, 40 });
                fallbackMenu->addChild(myButton);
                this->addChild(fallbackMenu, 100); // Prioridad alta para visibilidad
            }
        }

        return true;
    }

    /**
     * Callback del botón: Llama al proceso de autenticación real.
     */
    void onMyButton(CCObject* sender) {
        // Instanciamos el autenticador para iniciar la petición a la API
        Authenticator auth;
        auth.startAuthProcess();
    }
};