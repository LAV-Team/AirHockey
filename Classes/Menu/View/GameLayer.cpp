//
// Created by liza_shch on 16.11.18.
//

#include "GameLayer.h"

USING_NS_CC;

GameLayer* GameLayer::createLayer(GameSceneViewController *scene) {
    GameLayer *layer = GameLayer::create();
    layer->scene = scene;

    return layer;
}

void GameLayer::setupUI() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("Background.png");
    if (!backgroundSprite || backgroundSprite->getContentSize().width <= 0 ||
        backgroundSprite->getContentSize().height <= 0) {
        return;
    }

    backgroundSprite->setScale(visibleSize.width / backgroundSprite->getContentSize().width,
                               visibleSize.height / backgroundSprite->getContentSize().height);
    backgroundSprite->setAnchorPoint(Vec2(0, 0));
    backgroundSprite->setPosition(0, 0);
    this->addChild(backgroundSprite);

    auto closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            CC_CALLBACK_1(GameSceneViewController::gameCloseCallback, scene));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0) {
    } else {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    this->addChild(closeItem);
}

bool GameLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    setupUI();


    return true;
}



