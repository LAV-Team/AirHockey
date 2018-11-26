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

void GameController::touchHandler(cocos2d::Vec2 position) {
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float sceneWidth = visibleSize.width;
    float playerRadius = player1->getContentSize().width / 2;
    
    if (position.x > sceneWidth / 2 + playerRadius) {
        movePlayer(player1, position);
    }
    
    if (gameMode == twoPlayersOnDevice) {
        if (position.x < sceneWidth / 2 - playerRadius) {
            movePlayer(player2, position);
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
    
    if (gameMode == withComputer) {
        computerBehavior(ballPosition, difficulty);
    }
    
}

void GameController::startNewRound() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    ball->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    ball->getPhysicsBody()->setVelocity(Vec2(0, 0));
    ball->getPhysicsBody()->applyImpulse(Vec2(20000, 20000));
    
}

void GameController::computerBehavior(Vec2 ballPosition, Difficulty difficulty) {
    // works very bad
    
    
    float duration; // change based on difficulty
    
    switch (difficulty) {
        case easy:
            duration = 0.3;
            break;
        case medium:
            duration = 0.2;
            break;
        case hard:
            duration = 0.1;
            break;
        default:
            return;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto player2Position = player2->getPosition();
    auto player2Size = player2->getContentSize();
    
//    if (abs(ballPosition.x - player2Position.x) < player2Size.width / 2 + ball->getContentSize().width / 2) {
//        player2->stopActionByTag(1);
//        return;
//    }

    
    float randomX = (arc4random() % (int)visibleSize.width / 4);
    
    while (randomX > ballPosition.x && ballPosition.x > origin.x) {
        randomX /= 2;
    }
    
    
    Vec2 destinationY = Vec2(player2Position.x, ballPosition.y);
    Vec2 newPositionY = setPositionInSafeArea(player2, destinationY);
    Vec2 deltaMoveY = Vec2(0, ballPosition.y -  player2Position.y);
    
    Vec2 destinationX = Vec2(randomX, player2Position.y);
    Vec2 newPositionX = setPositionInSafeArea(player2, destinationX);
    Vec2 deltaMoveX = Vec2(newPositionX.x - player2Position.x, 0);
    
    auto moveY = MoveBy::create(0, deltaMoveY);
    moveY->setTag(0);
    if (player2->getNumberOfRunningActionsByTag(0) == 0) {
        player2->runAction(moveY);
    }
    
    auto moveX = MoveBy::create(duration * 5, deltaMoveX);
    moveX->setTag(1);
    if (player2->getNumberOfRunningActionsByTag(1) == 0) {
        player2->runAction(moveX);
    }
    
    
}


void GameController::keyboardHandler(EventKeyboard::KeyCode keyCode) {
    
    switch (keyCode) {
        case UP_ARROW:
            movePlayerKeyboard(player1, up);
            break;
        case DOWN_ARROW:
            movePlayerKeyboard(player1, down);
            break;
        case LEFT_ARROW:
            movePlayerKeyboard(player1, left);
            break;
        case RIGHT_ARROW:
            movePlayerKeyboard(player1, right);
            break;
        default:
            break;
    }
    
    if (gameMode == twoPlayersOnDevice) {
        switch (keyCode) {
            case KEY_W:
                movePlayerKeyboard(player2, up);
                break;
            case KEY_S:
                movePlayerKeyboard(player2, down);
                break;
            case KEY_A:
                movePlayerKeyboard(player2, left);
                break;
            case KEY_D:
                movePlayerKeyboard(player2, right);
                break;
            default:
                break;
        }
    }
    
}

void GameController::movePlayerKeyboard(Sprite* player, Direction direction) {
    auto oldPosition = player->getPosition();
    auto newPosition = oldPosition;
    auto playerSize = player->getContentSize();
    
    const float yStep = playerSize.height / 20;
    const float xStep = playerSize.width / 20;
    
    switch (direction) {
        case up:
            newPosition.y = oldPosition.y + yStep;
            break;
        case down:
            newPosition.y = oldPosition.y - yStep;
            break;
        case left:
            newPosition.x = oldPosition.x - xStep;
            break;
        case right:
            newPosition.x = oldPosition.x + xStep;
            break;
    }
    
    movePlayer(player, newPosition);
}

void GameController::movePlayer(Sprite *player, Vec2 position) {
    Vec2 newPosition = setPositionInSafeArea(player, position);
    
    auto moveAction = MoveTo::create(0, newPosition);
    player->stopAllActions();
    player->runAction(moveAction);
}

Vec2 GameController::setPositionInSafeArea(Sprite* player, Vec2 position) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size playerSize = player1->getContentSize();
    
    Vec2 newPosition = position;
    
    float maxY = origin.y + visibleSize.height - playerSize.height / 2;
    float minY = origin.y + playerSize.height / 2;
    float maxX = origin.x + visibleSize.width - playerSize.width / 2;
    float minX = origin.x + playerSize.width / 2;
    
    if (player == player1) {
        minX = minX + visibleSize.width / 2;
    } else if (player == player2) {
        maxX = maxX - visibleSize.width / 2;
    }
    
    if (position.x < minX) {
        newPosition.x = minX;
    }
    if (position.x > maxX) {
        newPosition.x = maxX;
    }
    if (position.y < minY) {
        newPosition.y = minY;
    }
    if (position.y > maxY) {
        newPosition.y = maxY;
    }
    
    return newPosition;
}
