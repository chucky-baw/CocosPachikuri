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
#include "GameOverScene.hpp"
#include <vector>

USING_NS_CC;

const float TIME_LIMIT_SECOND = 100;


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
    roombaBody->setCategoryBitmask(3);
    roombaBody->setContactTestBitmask(3);
    roombaBody->setCollisionBitmask(3);
    roombaBody->setTag(1);
    //減速させる関数を毎フレーム呼ぶ
   this->schedule(schedule_selector(HelloWorld::VelUpdate));
    
    roomba->setPhysicsBody(roombaBody);
    
    //猫描画
    auto cat = Sprite::create("/Users/sasakiyusei/Documents/cocos/CocosPachikuri/Resources/cat.png");
    cat->setAnchorPoint(Vec2(0.5, 0.5));
    cat->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 40));
    cat->setScale(0.3, 0.3);
    cat->setTag(3);
    this->addChild(cat, 1);
    
    Size catSize = Size(cat->getContentSize().width, cat->getContentSize().height);
    
    //猫の物理特性
    auto catBody = PhysicsBody::createCircle(catSize.width / 2);
    catBody->setMass(1.0f);
    catBody->setDynamic(false);
    catBody->setRotationEnable(false);
    catBody->setTag(4);
    catBody->setCategoryBitmask(1);
    catBody->setContactTestBitmask(1);
    catBody->setCollisionBitmask(1);
    cat->setPhysicsBody(catBody);
    
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

    collisionListener->onContactPreSolve = CC_CALLBACK_2(HelloWorld::_OnContactPreSolve, this);
    this->getEventDispatcher()->addEventListenerWithFixedPriority(collisionListener, 10);
    
    //ルンバと猫の衝突
    auto catCollisionListener = EventListenerPhysicsContact::create();
    
    catCollisionListener->onContactPreSolve = CC_CALLBACK_2(HelloWorld::catCollision, this);
    
    this->getEventDispatcher()->addEventListenerWithFixedPriority(catCollisionListener, 11);
    
    
    
    return true;
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

void HelloWorld::VelUpdate(float dt)
{
    if(_second > 0){
    Sprite* character = (Sprite*)this->getChildByTag(1);
    auto nowVel = character->getPhysicsBody()->getVelocity();
    float force = 0.92f;
        
    character->getPhysicsBody()->setVelocity(Vec2(nowVel.x * force, nowVel.y * force));
    }
    //制限時間減らしていく
    _second -= dt;
    int second = static_cast<int>(_second);
 _secondLabel->setString(StringUtils::toString(second));
    if(second == 0 && this->transitionFade == true)
    {
        if(this->transitionFade)
        {
            transitionFade = false;
            gameOverMove();
        }
    }
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
    sprite->getPhysicsBody()->setCategoryBitmask(1);
    sprite->getPhysicsBody()->setContactTestBitmask(1);
    sprite->getPhysicsBody()->setCollisionBitmask(1);
    sprite->getPhysicsBody()->setTag(5);
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
    if((contact.getShapeA()->getBody()->getTag() == 5 && contact.getShapeB()->getBody()->getTag() == 1)){
    nodeA->removeFromParent();
    trashCount--;
    }
    //log("trashCount = %i", trashCount);
    
    if (trashCount == 0)
    {
        clearMove();
    }
    //ここをfalseにすることですり抜けを実現
    return false;
}

//ねことルンバの衝突
bool HelloWorld::catCollision(PhysicsContact& contact, PhysicsContactPreSolve &solve)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    if((contact.getShapeA()->getBody()->getTag() == 4 && contact.getShapeB()->getBody()->getTag() == 1))
    {
    auto sprite = (Sprite*)this->getChildByTag(3);
        auto moveto = MoveTo::create(1, Vec2(sprite->getPosition().x + 3, sprite->getPosition().y));
    log("痛え");
    sprite->runAction(moveto);
        return true;
    }
    return false;
}

void HelloWorld::clearMove()
{
    auto scene = ClearScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.5f, scene, Color3B::WHITE));
    return;
}

void HelloWorld::gameOverMove()
{
    auto scene = GameOverScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(1.5f, scene, Color3B::BLACK));
    
    return;
}
                                   
