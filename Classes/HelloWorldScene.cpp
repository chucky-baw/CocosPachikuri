/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ClearScene.hpp"
#include <vector>

USING_NS_CC;

const float TIME_LIMIT_SECOND = 40;


Scene* HelloWorld::createScene()
{
    //物理演算があるシーンを生成
    auto scene = Scene::createWithPhysics();
    auto world = scene->getPhysicsWorld();
    world->setGravity(Vec2(0, 0));
    world->setSpeed(1.0f);
    world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

HelloWorld::HelloWorld()
:_second(TIME_LIMIT_SECOND)
, _secondLabel(NULL)
{
    
}

HelloWorld::~HelloWorld()
{
    CC_SAFE_RELEASE_NULL(_secondLabel);
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    if(!Scene::initWithPhysics()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //背景描画
    auto bg = Sprite::create("/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/Floor.jpg");
    bg->setAnchorPoint(Vec2(0.5, 0.5));
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    bg->setScale(2.0, 2.0);
    this->addChild(bg, 1);
    
    
    //残り時間描画
    
    int second = static_cast<int>(_second);
    auto secondLabel = Label::createWithSystemFont(StringUtils::toString(second), "MarkerFelt", 16);
    this->setSecondLabel(secondLabel);
    secondLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 300));
    this->addChild(secondLabel, 5);
    
    
    //ルンバ描画
    auto roomba = Sprite::create("/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/Roomba.png");
    roomba->setAnchorPoint(Vec2(0.5, 0.5));
    roomba->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 25));
    roomba->setScale(0.2, 0.2);
    roomba->setTag(1);
    this->addChild(roomba, 1);
    
    auto material = PHYSICSBODY_MATERIAL_DEFAULT;
    material.restitution = 0.8f;
    material.friction = 0.0f;
    
    
    Size roombaSize = Size(roomba->getContentSize().width, roomba->getContentSize().height / 2);
    //ルンバの物理特性
    auto roombaBody = PhysicsBody::createBox(roombaSize, material);
    roombaBody->setMass(1.0f);
    roombaBody->setDynamic(true);
    roombaBody->setRotationEnable(false);
    roombaBody->setCategoryBitmask(1);
    roombaBody->setContactTestBitmask(2);
    roombaBody->setCollisionBitmask(2);
    //減速させる関数を毎フレーム呼ぶ
    this->schedule(schedule_selector(HelloWorld::Update));
    roomba->setPhysicsBody(roombaBody);
    
    //壁描画部分
    auto verticalSpriteWall = Sprite::create("/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/VerticalWall.png");
    auto horizontalSpriteWall = Sprite::create("/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/HorizontalWall.png");
    
    auto leftyVerticalWall = addNewWall(this, Vec2(origin.x - verticalSpriteWall->getContentSize().width / 2, origin.y + visibleSize.height / 2), 1.0f, 2.5f, false, "/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/VerticalWall.png");
    
    
    auto rightVerticalWall = addNewWall(this, Vec2(origin.x + visibleSize.width +  verticalSpriteWall->getContentSize().width / 2, origin.y + visibleSize.height / 2), 1.0f, 2.5f, false, "/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/VerticalWall.png");
    
    auto topWall = addNewWall(this, Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height + horizontalSpriteWall->getContentSize().height / 2), 2.0f, 1.0f, false, "/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/HorizontalWall.png");
    
    auto bottomWall = addNewWall(this, Vec2(origin.x + visibleSize.width / 2, origin.y - horizontalSpriteWall->getContentSize().height / 2), 2.0f, 1.0f, false, "/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/HorizontalWall.png");
    
    
    //ゴミの座標配列
    Vec2 TrashVec[7]{
        Vec2(origin.x + 23, origin.y + 100),
        
        Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2),
        
        Vec2(origin.x + 145, origin.y + 56),
        
        Vec2(origin.x + 43, origin.y + 165),
        
        Vec2(origin.x + 143, origin.y + 174),
        
        Vec2(origin.x + 138, origin.y + 264),
        
         Vec2(origin.x + 77, origin.y + 260)
    };
    
    for (int i=0; i<7; i++)
    {
    //ゴミ描画
    auto gomi = addNewTrash(this, TrashVec[i], true, "/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/gomi_kamikuzu.png");
    }
    
    //タッチイベント部分
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::OnTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::OnTouchEnded, this);
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    //ゴミとルンバの衝突、消滅部分
    auto collisionListener = EventListenerPhysicsContact::create();
//    collisionListener->onContactPreSolve = [this](PhysicsContact &contact)->bool
//    {
//        auto nodeA = contact.getShapeA()->getBody()->getNode();
//        auto nodeB = contact.getShapeB()->getBody()->getNode();
//        nodeA->removeFromParent();
//        return true;
//    };
//    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(collisionListener, this);
    collisionListener->onContactPreSolve = CC_CALLBACK_2(HelloWorld::_OnContactPreSolve, this);
    this->getEventDispatcher()->addEventListenerWithFixedPriority(collisionListener, 10);
    
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
//    auto closeItem = MenuItemImage::create(
//                                           "CloseNormal.png",
//                                           "CloseSelected.png",
//                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
//
//    if (closeItem == nullptr ||
//        closeItem->getContentSize().width <= 0 ||
//        closeItem->getContentSize().height <= 0)
//    {
//        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
//    }
//    else
//    {
//        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
//        float y = origin.y + closeItem->getContentSize().height/2;
//        closeItem->setPosition(Vec2(x,y));
//    }
//
//    // create menu, it's an autorelease object
//    auto menu = Menu::create(closeItem, NULL);
//    menu->setPosition(Vec2::ZERO);
//    this->addChild(menu, 1);
//
//    /////////////////////////////
//    // 3. add your codes below...
//
//    // add a label shows "Hello World"
//    // create and initialize a label
//
//    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
//    if (label == nullptr)
//    {
//        problemLoading("'fonts/Marker Felt.ttf'");
//    }
//    else
//    {
//        // position the label on the center of the screen
//        label->setPosition(Vec2(origin.x + visibleSize.width/2,
//                                origin.y + visibleSize.height - label->getContentSize().height));
//
//        // add the label as a child to this layer
//        this->addChild(label, 1);
//    }
//
//    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//    if (sprite == nullptr)
//    {
//        problemLoading("'HelloWorld.png'");
//    }
//    else
//    {
//        // position the sprite on the center of the screen
//        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//        // add the sprite as a child to this layer
//        this->addChild(sprite, 0);
//    }
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

bool HelloWorld::OnTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    auto sPos = touch->getLocation();
    startPos = sPos;
    log("startPos = %f, %f", startPos.x, startPos.y);
    return true;
}

void HelloWorld::OnTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Sprite* character = (Sprite*)this->getChildByTag(1);
    auto ePos = touch->getLocation();
    endPos = ePos;
    //射出方向の計算
    Direction = -1 * (endPos - startPos);
    //Direction.normalize();
    
    float force = 2.0f;
    character->getPhysicsBody()->applyImpulse(Direction * force, Direction * force / 2.0f);
    
    log("Direction = %f, %f", Direction.x, Direction.y);
    return;
}

void HelloWorld::Update(float dt)
{
    Sprite* character = (Sprite*)this->getChildByTag(1);
    auto nowVel = character->getPhysicsBody()->getVelocity();
    float force = 0.92f;
    character->getPhysicsBody()->setVelocity(Vec2(nowVel.x * force, nowVel.y * force));
    
    //制限時間減らしていく
    _second -= dt;
    int second = static_cast<int>(_second);
    _secondLabel->setString(StringUtils::toString(second));
}

Sprite* HelloWorld::addNewWall(Node *parent, Vec2 p, float widthScale, float heightScale, bool dynamic, const char *fileName)
    {
        Sprite* sprite = Sprite::create(fileName);
        auto material = PHYSICSBODY_MATERIAL_DEFAULT;
        material.density     = 1.0f; // 密度
        material.restitution = 1.0f; // 反発係数
        material.friction    = 0.0f; // 摩擦係数
        sprite->setPhysicsBody(PhysicsBody::createBox(sprite->getContentSize(), material));
        sprite->getPhysicsBody()->setDynamic(dynamic);
        sprite->setPosition(p);
        sprite->setScale(widthScale, heightScale);
        parent->addChild(sprite, 10);
        return sprite;
    }

Sprite* HelloWorld::addNewTrash(Node *parent, Vec2 v, bool dynamic, const char *fileName)
{
    Sprite* sprite = Sprite::create(fileName);
    auto material = PHYSICSBODY_MATERIAL_DEFAULT;
    material.restitution = 0.0f;
    sprite->setPhysicsBody(PhysicsBody::createCircle(sprite->getContentSize().width / 2, material));
    sprite->getPhysicsBody()->setDynamic(dynamic);
    sprite->getPhysicsBody()->setCategoryBitmask(2);
    sprite->getPhysicsBody()->setContactTestBitmask(1);
    sprite->getPhysicsBody()->setCollisionBitmask(1);
    sprite->setPosition(v);
    sprite->setScale(0.25f);
    parent->addChild(sprite, 10);
    trashCount++;
    log("trashCount = %i", trashCount);
    return sprite;
}

bool HelloWorld::_OnContactPreSolve(PhysicsContact &contact, PhysicsContactPreSolve &solve)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    nodeA->removeFromParent();
    trashCount--;
    //log("trashCount = %i", trashCount);
    
    if (trashCount == 0)
    {
        clearMove();
    }
    //ここをfalseにすることですり抜けを実現
    return false;
}

void HelloWorld::clearMove()
{
    auto scene = ClearScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.5f, scene, Color3B::WHITE));
    
}
                                   
                                   
