//
//  GameOverScene.cpp
//  Pachikuri-mobile
//
//  Created by 佐々木勇星 on 2020/01/13.
//

#include "GameOverScene.hpp"
#include "HelloWorldScene.h"
#include "TitleScene.hpp"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

cocos2d::Scene* GameOverScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOverScene::create();
    scene->addChild(layer);
    return scene;
}

GameOverScene::~GameOverScene()
{
    removeAllChildrenWithCleanup(true);
}

bool GameOverScene::init()
{
    if(!Scene::init())
    {
        return false;
    }
    
    //BGMストップ
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    //SE再生
    SimpleAudioEngine::getInstance()->setEffectsVolume(0.3f);
    SimpleAudioEngine::getInstance()->playEffect("Over.mp3");
    
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto bg = Sprite::create("/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/GameOverScene.png");
    bg->setAnchorPoint(Vec2(0.5, 0.5));
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    bg->setScale(1.0f, 1.0f);
    this->addChild(bg);
    
    auto mentenance = Sprite::create("/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/mentenance.png");
    mentenance->setAnchorPoint(Vec2(0.5, 0.5));
    mentenance->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 15));
    mentenance->setScale(0.8f, 0.8f);
    this->addChild(mentenance, 2);
    
    //各ボタンを作成
//    auto againButton = MenuItemImage::create("/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/pushedAgainButton.png", "/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/pushedAgainButton.png", CC_CALLBACK_1(GameOverScene::pushAgain, this));
    
    auto againButton = MenuItemImage::create("/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/pushedAgainButton.png", "/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/pushedAgainButton.png", CC_CALLBACK_1(GameOverScene::pushAgain, this));
    
    auto backButton = MenuItemImage::create("/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/backButton.png", "/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/pushedBackbutton.png", CC_CALLBACK_1(GameOverScene::pushBack, this));
    
    againButton->setScale(0.6f);
    againButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 10));
    
    backButton->setScale(0.6f);
    backButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 35));
    
    auto menu = Menu::create(againButton, backButton, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    /////////テスト////////////
//    auto listener = EventListenerTouchOneByOne::create();
//    listener->onTouchBegan = [this](Touch* touch, Event* event)
//    {
//        //一度押したらアクションを無効化
//        this->getEventDispatcher()->removeAllEventListeners();
//        //0.5s待機してからcallFuncを呼ぶ
//        auto delay = DelayTime::create(0.5);
//
//        auto startGame = CallFunc::create([]{
//            auto scene = HelloWorld::createScene();
//            //シーン移動
//            auto transition = TransitionProgressInOut::create(1.5, scene);
//            Director::getInstance()->replaceScene(transition);
//
//        });
//
//        this->runAction(Sequence::create(delay, startGame, NULL));
//
//
//        return true;
//    };
//
//    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void GameOverScene::pushAgain(Ref *pSender)
{
    CCLOG("push again button");
    
    //もう一度ゲーム画面に戻る
    auto delay = DelayTime::create(0.5);
//
//    auto startGame = CallFunc::create([]{
//        auto scene = HelloWorld::createScene();
//
//        auto transition = TransitionProgressInOut::create(1.5, scene);
//
//        Director::getInstance()->replaceScene(transition);
//    });
    Scene *scene = HelloWorld::createScene();
    //Director::getInstance()->replaceScene(scene);
    //this->runAction(Sequence::create(delay, startGame, NULL));
    
    return;
    
}

void GameOverScene::pushBack(Ref *pSender)
{
    CCLOG("push back button");
    SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
    SimpleAudioEngine::getInstance()->playEffect("TapButton.mp3");
    Director::getInstance()->replaceScene( TitleScene::createScene());
}
