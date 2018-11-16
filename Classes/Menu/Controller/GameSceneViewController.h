//
// Created by liza_shch on 16.11.18.
//

#ifndef TEMPLATECPP_GAMESCENEVIEWCONTROLLER_H
#define TEMPLATECPP_GAMESCENEVIEWCONTROLLER_H

#include "cocos2d.h"
#include "GameLayer.h"

class GameLayer;

class GameSceneViewController: public cocos2d::Scene {
private:
    GameLayer *gameLayer;
public:
    GameSceneViewController(){}
    virtual ~GameSceneViewController(){}
    static cocos2d::Scene* createScene();
    virtual bool init();
    void gameCloseCallback(Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameSceneViewController);
};


#endif //TEMPLATECPP_GAMESCENEVIEWCONTROLLER_H
