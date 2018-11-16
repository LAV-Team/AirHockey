//
// Created by liza_shch on 16.11.18.
//

#include "GameSceneViewController.h"

USING_NS_CC;

cocos2d::Scene * GameSceneViewController::createScene() {
    return GameSceneViewController::create();
}

bool GameSceneViewController::init() {
    if (!Scene::init()) {
        return false;
    }

    gameLayer = GameLayer::createLayer(this);
    addChild(gameLayer);

    return true;
}

void GameSceneViewController::gameCloseCallback(cocos2d::Ref *pSender) {
    Director::getInstance()->end();
}