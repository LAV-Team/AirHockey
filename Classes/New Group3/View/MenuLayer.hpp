//
//  MenuLayer.hpp
//  AirHockey-mobile
//
//  Created by Artur on 02/11/2018.
//

#ifndef MenuLayer_hpp
#define MenuLayer_hpp

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "MenuLabel.hpp"
#include "MenuViewController.hpp"

class MenuViewController;

class MenuLayer: public cocos2d::Layer {
private:
    MenuViewController* controller;
    void setupUI();
    virtual bool init();
public:
    cocos2d::Label* testLabel;
    static MenuLayer* createLayer(MenuViewController* controller);
    MenuLayer();
    ~MenuLayer();
    
    CREATE_FUNC(MenuLayer);
};


#endif /* MenuLayer_hpp */
