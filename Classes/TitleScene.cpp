//
//  TitleScene.cpp
//  Pachikuri-mobile
//
//  Created by 佐々木勇星 on 2020/01/15.
//

#include "TitleScene.hpp"
USING_NS_CC;

cocos2d::Scene* TitleScene::createScene()
{
    auto scene = Scene::create();
    auto layer = TitleScene::create();
    scene->addChild(layer);
    return scene;
}

bool TitleScene::init()
{
    if(!Scene::init())
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    auto startLabel = Label::createWithSystemFont("Tap To Start", "/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/fonts/arial.ttf", 14);
    startLabel->setAnchorPoint(Vec2(0.5, 0.5));
    startLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 25));
    this->addChild(startLabel, 1);
    
    auto bg = Sprite::create("/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/TitleScene.png");
    bg->setAnchorPoint(Vec2(0.5, 0.5));
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    bg->setScale(2.0f, 2.0f);
    this->addChild(bg);
    
    return true;

}
