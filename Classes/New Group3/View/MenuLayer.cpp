//
//  MenuLayer.cpp
//  AirHockey-mobile
//
//  Created by Artur on 02/11/2018.
//

#include "MenuLayer.hpp"

USING_NS_CC;

MenuLayer::MenuLayer() {
    std::cout << "\nMenuLayer allocated" << std::endl;
}

MenuLayer::~MenuLayer() {
    std::cout << "\nMenuLayer deallocated" << std::endl;
}

MenuLayer* MenuLayer::createLayer(MenuViewController* controller) {
    MenuLayer* layer = MenuLayer::create();
    layer->controller = controller;
    
    return layer;
}

static void problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void MenuLayer::setupUI() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MenuViewController::menuCloseCallback, controller));
    
    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0) {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    } else {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }
    
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    testLabel = MenuLabel::create("Airhockey");
    
    if (testLabel == nullptr) {
        problemLoading("'fonts/Marker Felt.ttf'");
    } else {
        testLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - testLabel->getContentSize().height));
        
        this->addChild(testLabel, 1);
    }
    
}

bool MenuLayer::init(){
    if (!Layer::init()) {
        return false;
    }
    
    setupUI();
    
    return true;
}

