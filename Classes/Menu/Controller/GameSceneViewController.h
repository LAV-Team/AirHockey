//
// Created by liza_shch on 16.11.18.
//

#ifndef TEMPLATECPP_GAMESCENEVIEWCONTROLLER_H
#define TEMPLATECPP_GAMESCENEVIEWCONTROLLER_H


#include "cocos2d.h"
#include "GameLayer.h"
#include "GameController.hpp"


class GameLayer;
class GameController;

class GameSceneViewController: public cocos2d::Scene {
private:
    GameLayer* gameLayer;
public:
    GameController* controller;
    GameSceneViewController(){}
    virtual ~GameSceneViewController();
    static cocos2d::Scene* createScene();
    virtual bool init();
    void gameCloseCallback(Ref* pSender);
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void update(float delta);


    // implement the "static create()" method manually
    CREATE_FUNC(GameSceneViewController);
};


#endif //TEMPLATECPP_GAMESCENEVIEWCONTROLLER_H
