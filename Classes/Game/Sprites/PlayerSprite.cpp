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
    
    auto radius = visibleSize.height / 15;
    auto playerSize = Size(2 * radius, 2 * radius);

    player->setContentSize(playerSize);
    player->setPosition(position);
    
    auto physicsBody = PhysicsBody::createCircle(radius, PhysicsMaterial(0.1f, 1, 0));

    physicsBody->setDynamic(false);
    player->setPhysicsBody(physicsBody);
    
    
    return player;
    
    
}
