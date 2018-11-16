//
//  MenuLabel.hpp
//  AirHockey-mobile
//
//  Created by Artur on 03/11/2018.
//

#ifndef MenuLabel_hpp
#define MenuLabel_hpp

#include <stdio.h>
#include "cocos2d.h"

class MenuLabel {
public:
    static cocos2d::Label* create(const std::string &text);
    static int fontSize;
};

#endif /* MenuLabel_hpp */
