//
//  MenuLabel.cpp
//  AirHockey-mobile
//
//  Created by Artur on 03/11/2018.
//

#include "MenuLabel.hpp"

USING_NS_CC;

int MenuLabel::fontSize = 24;

Label* MenuLabel::create(const std::string &text) {
    auto label = Label::createWithTTF(text, "fonts/Marker Felt.ttf", fontSize);
    label->setColor(Color3B::WHITE);

    return label;
}
