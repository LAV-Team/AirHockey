//
// Created by liza_shch on 16.11.18.
//

#include "GameSceneViewController.h"

USING_NS_CC;


GameSceneViewController::~GameSceneViewController() {
    delete controller;
    controller = nullptr;
}


cocos2d::Scene * GameSceneViewController::createScene() {
    auto scene = Scene::createWithPhysics();
    
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    
    auto sceneLayer = GameSceneViewController::create();
    scene->addChild(sceneLayer);
    
    return scene;
    
}

bool GameSceneViewController::init() {
    if (!Scene::init()) {
        return false;
    }
    
    auto layer = GameLayer::createLayer(this);
    addChild(layer);

    controller = new GameController(this);
    
    
    
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = CC_CALLBACK_2(GameSceneViewController::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameSceneViewController::onTouchMoved, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    

    return true;
}

void GameSceneViewController::gameCloseCallback(cocos2d::Ref *pSender) {
    Director::getInstance()->end();
}


bool GameSceneViewController::onTouchBegan(Touch* touch, Event* event) {
    controller->updatePosition(touch->getLocation());
    return true;
}

void GameSceneViewController::onTouchMoved(Touch* touch, Event* event) {
    controller->updatePosition(touch->getLocation());
}
