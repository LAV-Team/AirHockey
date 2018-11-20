//
//  GameController.hpp
//  AirHockey-mobile
//
//  Created by Artur on 03/11/2018.
//

#ifndef GameController_hpp
#define GameController_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "PlayerSprite.hpp"
#include "BallSprite.hpp"
#include "Edges.hpp"
#include "Shared.hpp"

class GameLayer;

class GameController {
private:
    cocos2d::Scene* scene;
    cocos2d::Sprite* player1;
    cocos2d::Sprite* player2;
    cocos2d::Sprite* ball;

    void setupGameScene();
public:
    GameController(cocos2d::Scene* scene);
    virtual ~GameController();

    enum Direction {
        up,
        down,
        left,
        right
    };
    
    void touchHandler(cocos2d::Vec2 position);
    void update();
    void startNewRound();
    void computerBehavior(cocos2d::Vec2 ballPosition);
    void keyboardHandler(cocos2d::EventKeyboard::KeyCode keyCode);
    void movePlayerKeyboard(cocos2d::Sprite* player, Direction direction);
    void movePlayer(cocos2d::Sprite* player, cocos2d::Vec2 position);
    cocos2d::Vec2 setPositionInSafeArea(cocos2d::Vec2 position);
    

};

#endif /* GameController_hpp */
