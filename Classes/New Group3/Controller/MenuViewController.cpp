//
//  MenuViewController.cpp
//  AirHockey-mobile
//
//  Created by Artur on 03/11/2018.
//

#include "MenuViewController.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC;

MenuViewController::MenuViewController() {
    std::cout << "\nMenuViewController allocated" << std::endl;
    
}

MenuViewController::~MenuViewController() {
    std::cout << "\nMenuViewController deallocated" << std::endl;
}

Scene* MenuViewController::createScene() {
    return MenuViewController::create();
}

bool MenuViewController::init() {
    if (!Scene::init()) {
        return false;
    }
    
    menuLayer = MenuLayer::createLayer(this);
    addChild(menuLayer);
    
    return true;
}

void MenuViewController::menuCloseCallback(Ref* pSender) {
    //Close the cocos2d-x game scene and quit the application
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
}
