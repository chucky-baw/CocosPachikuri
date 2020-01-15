//
//  TitleScene.cpp
//  Pachikuri-mobile
//
//  Created by 佐々木勇星 on 2020/01/15.
//

#include "TitleScene.hpp"
#include "HelloWorldScene.h"
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
    
    auto startLabel = Label::createWithSystemFont("Tap To Start", "/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/fonts/arial.ttf", 16);
    startLabel->setAnchorPoint(Vec2(0.5, 0.5));
    startLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 25));
    startLabel->enableBold();
    this->addChild(startLabel, 1);
    
    auto blink = Blink::create(1.2, 1);
    auto repeat = RepeatForever::create(blink);
    
    startLabel->runAction(repeat);
    
    
    auto bg = Sprite::create("/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/TitleScene.png");
    bg->setAnchorPoint(Vec2(0.5, 0.5));
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    bg->setScale(2.0f, 2.0f);
    this->addChild(bg);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch* touch, Event* event)
    {
        //一度押したらアクションを無効化
        this->getEventDispatcher()->removeAllEventListeners();
        //0.5s待機してからcallFuncを呼ぶ
        auto delay = DelayTime::create(0.5);
        
        auto startGame = CallFunc::create([]{
            auto scene = HelloWorld::createScene();
            //シーン移動
            auto transition = TransitionProgressInOut::create(1.5, scene);
            Director::getInstance()->replaceScene(transition);
            
        });
        
        this->runAction(Sequence::create(delay, startGame, NULL));
        
        
        return true;
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;

}


