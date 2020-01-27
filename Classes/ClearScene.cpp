//
//  ClearScene.cpp
//  Pachikuri-mobile
//
//  Created by 佐々木勇星 on 2020/01/07.
//
#pragma execution_character_set("utf-8")

#include "ClearScene.hpp"
#include "TitleScene.hpp"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;

cocos2d::Scene* ClearScene::createScene()
{
    auto scene = Scene::create();
    auto layer = ClearScene::create();
    scene->addChild(layer);
    return scene;
}

bool ClearScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    //BGMストップ
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    SimpleAudioEngine::getInstance()->playEffect("Clear.mp3");
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //タイトルに戻るのラベル
    auto clearLabel = Label::createWithSystemFont("タップしてタイトルに戻る", "/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/fonts/arial.ttf", 12);
    
    clearLabel->setAnchorPoint(Vec2(0.5, 0.5));
    clearLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 20));
    clearLabel->setTextColor(Color4B::BLACK);
    this->addChild(clearLabel, 1);
    
    auto blink = Blink::create(1.2, 1);
    auto repeat = RepeatForever::create(blink);
    
    clearLabel->runAction(repeat);
    
    
    auto bg = Sprite::create("/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/clearScene.png");
    bg->setAnchorPoint(Vec2(0.5, 0.5));
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    bg->setScale(2.0f, 2.0f);
    this->addChild(bg);
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = [this](Touch* touch, Event* event)
    {
        this->getEventDispatcher()->removeAllEventListeners();
        
        auto delay = DelayTime::create(0.5);
        
        auto backToTitle = CallFunc::create([]{
            auto scene = TitleScene::createScene();
            
            auto transition = TransitionFade::create(1.5f, scene, Color3B::WHITE);
            
            Director::getInstance()->replaceScene(transition);
        });
        
        SimpleAudioEngine::getInstance()->playEffect("TapButton.mp3");
        this->runAction(Sequence::create(delay, backToTitle, NULL));
        
        return true;
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
    
}
