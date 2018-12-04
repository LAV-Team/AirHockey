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

    auto backgroundSprite = Sprite::create("Background.png");
    if (!backgroundSprite || backgroundSprite->getContentSize().width <= 0 ||
        backgroundSprite->getContentSize().height <= 0) {
        problemLoading("'Background.png'");
    }

    backgroundSprite->setScale(visibleSize.width / backgroundSprite->getContentSize().width,
                               visibleSize.height / backgroundSprite->getContentSize().height);
    backgroundSprite->setAnchorPoint(Vec2(0, 0));
    backgroundSprite->setPosition(0, 0);
    this->addChild(backgroundSprite);

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

    std::map<MenuViewController::GameMode, std::string> gameModeList {
            {MenuViewController::GameMode::easy, "easy"},
            {MenuViewController::GameMode::medium, "medium"},
            {MenuViewController::GameMode::hard, "hard"},
            {MenuViewController::GameMode::twoPlayers, "2 players"},
            {MenuViewController::GameMode::online, "online"}
    };

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);

    float dy = MenuLabel::fontSize * 1.5;
    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height / 2 + 3 * dy;
    for (auto& item : gameModeList) {
        auto button = MenuItemLabel::create(MenuLabel::create(item.second),
                                            CC_CALLBACK_1(MenuViewController::playCallback, controller,
                                                          item.first));
        if(!button) {

        } else {
            y -= dy;
            button->setPosition(Vec2(x, y));
        }
        menu->addChild(button);
    }

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

