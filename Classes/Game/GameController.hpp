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


class GameController {
private:
    cocos2d::Scene* scene;
    cocos2d::Sprite* player1;
    cocos2d::Sprite* player2;
    cocos2d::Sprite* ball;


    void setupGameScene();
public:
    GameController(cocos2d::Scene* scene);
    void updatePosition(cocos2d::Vec2 position);
    virtual ~GameController();
    

};

#endif /* GameController_hpp */
