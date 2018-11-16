//
//  PlayerSprite.cpp
//  AirHockey-mobile
//
//  Created by Artur on 16/11/2018.
//

#include "PlayerSprite.hpp"

USING_NS_CC;


Sprite* PlayerSprite::create(PlayerSide side) {
    
    Sprite* player;
    Vec2 position;
    Size visibleSize = Director::getInstance()->getVisibleSize();

    switch (side) {
    
        case left:
            player = Sprite::create("Player1.png");
            position = Vec2(visibleSize.width / 4, visibleSize.height / 2);
            break;
        case right:
            player = Sprite::create("Player2.png");
            position = Vec2(visibleSize.width * 3 / 4, visibleSize.height / 2);
            break;
    }
    
    
    auto playerSize = Size(visibleSize.height / 5, visibleSize.height / 5);

    player->setContentSize(playerSize);
    player->setPosition(position);
    
    
    return player;
    
    
}
