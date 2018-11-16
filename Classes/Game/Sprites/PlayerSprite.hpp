//
//  PlayerSprite.hpp
//  AirHockey-mobile
//
//  Created by Artur on 16/11/2018.
//

#ifndef PlayerSprite_hpp
#define PlayerSprite_hpp

#include <stdio.h>
#include "cocos2d.h"


class PlayerSprite: public cocos2d::Sprite {
private:

public:
    enum PlayerSide {
        left, right
    };
    
    static cocos2d::Sprite* create(PlayerSide side);
};


#endif /* PlayerSprite_hpp */
