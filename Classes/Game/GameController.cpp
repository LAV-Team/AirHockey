//
//  GameController.cpp
//  AirHockey-mobile
//
//  Created by Artur on 03/11/2018.
//

#include "GameController.hpp"
#include <iostream>


USING_NS_CC;

GameController::GameController(Scene* scene) {
    this->scene = scene;
    setupGameScene();
}

GameController::~GameController() {
    
}

void GameController::setupGameScene() {
    
    auto edges = Edges::create();
    scene->addChild(edges);

    player2 = PlayerSprite::create(PlayerSprite::right);
    scene->addChild(player2);
    
    player1 = PlayerSprite::create(PlayerSprite::left);
    scene->addChild(player1);
    
    ball = BallSprite::create();
    scene->addChild(ball);
    
}

void GameController::updatePosition(cocos2d::Vec2 position) {
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float sceneWidth = visibleSize.width;
    float playerRadius = player1->getContentSize().width / 2;
    
    if (position.x < sceneWidth / 2 - playerRadius) {
        player1->setPosition(position);
    }
    
    bool twoPlayersOnDevice = true;
    if (twoPlayersOnDevice) {
        if (position.x > sceneWidth / 2 + playerRadius) {
            player2->setPosition(position);
        }
    }
    
    
}
