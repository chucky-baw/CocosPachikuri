//
//  GameOverScene.cpp
//  Pachikuri-mobile
//
//  Created by 佐々木勇星 on 2020/01/13.
//

#include "GameOverScene.hpp"
USING_NS_CC;

cocos2d::Scene* GameOverScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOverScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameOverScene::init()
{
    if(!Scene::init())
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto bg = Sprite::create("/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/GameOverScene.png");
    bg->setAnchorPoint(Vec2(0.5, 0.5));
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    bg->setScale(1.0f, 1.0f);
    this->addChild(bg, 2);
    
    return true;
}
