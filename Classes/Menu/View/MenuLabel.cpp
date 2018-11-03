//
//  MenuLabel.cpp
//  AirHockey-mobile
//
//  Created by Artur on 03/11/2018.
//

#include "MenuLabel.hpp"

USING_NS_CC;


Label* MenuLabel::create(const std::string &text) {
    auto label = Label::createWithTTF(text, "fonts/Marker Felt.ttf", 24);
    label->setColor(Color3B::BLUE);
    
    return label;
}
