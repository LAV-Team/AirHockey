//
//  BallSprite.cpp
//  AirHockey
//
//  Created by Artur on 17/11/2018.
//

#include "BallSprite.hpp"


USING_NS_CC;


Sprite* BallSprite::create() {
    
    Sprite* ball;
    Vec2 position;
    Size visibleSize = Director::getInstance()->getVisibleSize();
            
    ball = Sprite::create("Player1.png");
    
    auto radius = visibleSize.height / 30;
    auto ballSize = Size(2 * radius, 2 * radius);
    
    ball->setContentSize(ballSize);
    ball->setPosition(position);
    
    auto physicsBody = PhysicsBody::createCircle(radius, PhysicsMaterial(0.1f, 1, 0));
    //    physicsBody->setMass(1);
    
    ball->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    physicsBody->setLinearDamping(0);
    physicsBody->setAngularDamping(0);
    

    ball->setPhysicsBody(physicsBody);
    
    
    return ball;
    
    
}
