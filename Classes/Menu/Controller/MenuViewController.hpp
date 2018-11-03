//
//  MenuViewController.hpp
//  AirHockey-mobile
//
//  Created by Artur on 03/11/2018.
//


#ifndef MenuViewController_hpp
#define MenuViewController_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "MenuLayer.hpp"

class MenuLayer;

class MenuViewController: public cocos2d::Scene {
private:
    MenuLayer* menuLayer;
public:
    static cocos2d::Scene* createScene();
    MenuViewController();
    void menuCloseCallback(cocos2d::Ref* pSender);
    virtual ~MenuViewController();
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MenuViewController);
};

#endif /* MenuViewController_hpp */





