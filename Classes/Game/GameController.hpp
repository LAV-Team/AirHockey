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
#include "Sprites/PlayerSprite.hpp"
#include "Sprites/BallSprite.hpp"
#include "Sprites/Edges.hpp"
#include "Shared.hpp"
#include "../Menu/View/MenuLabel.hpp"


class GameLayer;
class MenuLabel;

class GameController {
private:
    cocos2d::Scene* scene;
    cocos2d::Sprite* player1;
    cocos2d::Sprite* player2;
    cocos2d::Sprite* ball;
    int player1Score;
    int player2Score;
    cocos2d::Label* player1ScoreLabel;
    cocos2d::Label* player2ScoreLabel;
    GameMode gameMode = twoPlayersOnDevice;
    Difficulty difficulty = hard;
    

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
    void computerBehavior(cocos2d::Vec2 ballPosition, Difficulty difficulty);
    void keyboardHandler(cocos2d::EventKeyboard::KeyCode keyCode);
    void movePlayerKeyboard(cocos2d::Sprite* player, Direction direction);
    void movePlayer(cocos2d::Sprite* player, cocos2d::Vec2 position);
    cocos2d::Vec2 setPositionInSafeArea(cocos2d::Sprite* player, cocos2d::Vec2 position);
    

};

#endif /* GameController_hpp */
