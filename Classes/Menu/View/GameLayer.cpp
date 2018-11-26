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

//    auto closeItem = MenuItemImage::create(
//            "CloseNormal.png",
//            "CloseSelected.png",
//            CC_CALLBACK_1(GameSceneViewController::gameCloseCallback, scene));
//
//    if (closeItem == nullptr ||
//        closeItem->getContentSize().width <= 0 ||
//        closeItem->getContentSize().height <= 0) {
//    } else {
//        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
//        float y = origin.y + closeItem->getContentSize().height/2;
//        closeItem->setPosition(Vec2(x,y));
//    }
//
//    this->addChild(closeItem);
}

bool GameLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    setupUI();
    
    this->schedule(schedule_selector(GameLayer::onKeyHold));
    setKeyboardEnabled(true);

    return true;
}



void GameLayer::onKeyHold(float interval){
    
    std::vector<cocos2d::EventKeyboard::KeyCode> keyCodes = {UP_ARROW, DOWN_ARROW, RIGHT_ARROW, LEFT_ARROW, KEY_W, KEY_S, KEY_A, KEY_D};
    
    for (int i = 0; i < keyCodes.size(); i++) {
        if(std::find(heldKeys.begin(), heldKeys.end(), keyCodes[i]) != heldKeys.end()){
            scene->controller->keyboardHandler(keyCodes[i]);
        }
    }

//    if(std::find(heldKeys.begin(), heldKeys.end(), UP_ARROW) != heldKeys.end()){
//        // up pressed
//    }
//
//    if(std::find(heldKeys.begin(), heldKeys.end(), DOWN_ARROW) != heldKeys.end()){
//        // down pressed
//    }
//
//    if(std::find(heldKeys.begin(), heldKeys.end(), RIGHT_ARROW) != heldKeys.end()){
//    }
//
//    if(std::find(heldKeys.begin(), heldKeys.end(), LEFT_ARROW) != heldKeys.end()){
//        // left pressed
//    }
//
//    if(std::find(heldKeys.begin(), heldKeys.end(), KEY_W) != heldKeys.end()){
//        // up pressed
//    }
//
//    if(std::find(heldKeys.begin(), heldKeys.end(), KEY_S) != heldKeys.end()){
//        // down pressed
//    }
//
//    if(std::find(heldKeys.begin(), heldKeys.end(), KEY_D) != heldKeys.end()){
//    }
//
//    if(std::find(heldKeys.begin(), heldKeys.end(), KEY_S) != heldKeys.end()){
//        // left pressed
//    }
    
}

void GameLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    
    if(std::find(heldKeys.begin(), heldKeys.end(), keyCode) == heldKeys.end()){
        heldKeys.push_back(keyCode);
    }
}

void GameLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), keyCode), heldKeys.end());
}


