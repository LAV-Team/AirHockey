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
    startNewRound();
}

GameController::~GameController() {
    
}

void GameController::setupGameScene() {
    
    auto edges = Edges::create();
    scene->addChild(edges);

    player1 = PlayerSprite::create(PlayerSprite::right);
    scene->addChild(player1);
    
    player2 = PlayerSprite::create(PlayerSprite::left);
    scene->addChild(player2);
    
    ball = BallSprite::create();
    scene->addChild(ball);
    
}

void GameController::updatePosition(cocos2d::Vec2 position) {
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float sceneWidth = visibleSize.width;
    float playerRadius = player1->getContentSize().width / 2;
    
    if (position.x > sceneWidth / 2 + playerRadius) {
        player1->setPosition(position);
    }

    bool twoPlayersOnDevice = true;
    if (twoPlayersOnDevice) {
        if (position.x < sceneWidth / 2 - playerRadius) {
            player2->setPosition(position);
        }
    }
    
}


void GameController::update() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Vec2 ballPosition = ball->getPosition();
    Size ballSize = ball->getContentSize();
    
    if (ballPosition.x < origin.x - ballSize.width / 2) {
        startNewRound();
    } else if ((ballPosition.x > origin.x + visibleSize.width + ballSize.width / 2)) {
        startNewRound();
    }
    
    bool withComputer = false;
    if (withComputer) {
        computerBehavior(ballPosition);
    }
}

void GameController::startNewRound() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    ball->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    ball->getPhysicsBody()->setVelocity(Vec2(0, 0));
    ball->getPhysicsBody()->applyImpulse(Vec2(20000, 20000));
    
}

void GameController::computerBehavior(Vec2 ballPosition) {
    
    // works very bad
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto player2Position = player2->getPosition();
    auto physicsBody = player2->getPhysicsBody();
    auto player2Size = player2->getContentSize();
    
    auto topEdge = Vec2(player2Position.x, origin.y + visibleSize.height * 4 / 5);
    auto bottomEdge = Vec2(player2Position.x, origin.y + visibleSize.height / 5);
    
    if (player2Position.y > topEdge.y + player2Size.height / 2) {
        player2->setPosition(topEdge);
    } else if (player2Position.y < bottomEdge.y - player2Size.height / 2) {
        player2->setPosition(bottomEdge);
    } else {
        auto velocity = Vec2(0, (ballPosition.y - player2Position.y) * 10);
        physicsBody->setVelocity(velocity);
    }
}
