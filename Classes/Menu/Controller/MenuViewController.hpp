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
#include "GameSceneViewController.h"

class MenuLayer;
class GameSceneViewController;

class MenuViewController: public cocos2d::Scene {
private:
    MenuLayer* menuLayer;
public:
    typedef enum {
        easy,
        medium,
        hard,
        twoPlayers,
        online
    } GameMode;

    static cocos2d::Scene* createScene();
    MenuViewController();
    void menuCloseCallback(Ref* pSender);
    void playCallback(Ref* pSender, GameMode gameMode);
    virtual ~MenuViewController();
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(MenuViewController);
};

#endif /* MenuViewController_hpp */





