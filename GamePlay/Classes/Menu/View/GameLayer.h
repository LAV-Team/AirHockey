//
// Created by liza_shch on 16.11.18.
//

#ifndef TEMPLATECPP_GAMELAYER_H
#define TEMPLATECPP_GAMELAYER_H

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "../Controller/GameSceneViewController.h"
#include "../../Game/Shared.hpp"

class GameSceneViewController;

class GameLayer: public cocos2d::Layer {
private:
    GameSceneViewController *scene;
    void setupUI();
    virtual bool init();
public:
    cocos2d::Label* testLabel;
    static GameLayer* createLayer(GameSceneViewController* scene);
    GameLayer(){}
    ~GameLayer(){}

    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    std::vector<cocos2d::EventKeyboard::KeyCode> heldKeys;
    
    void onKeyHold(float interval);
    CREATE_FUNC(GameLayer);
    
};


#endif //TEMPLATECPP_GAMELAYER_H
