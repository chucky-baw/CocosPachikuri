//
//  SceneMaker.cpp
//  Pachikuri-mobile
//
//  Created by 佐々木勇星 on 2020/01/13.
//

#include "SceneMaker.hpp"
USING_NS_CC;

SceneMaker::SceneMaker(const std::string &nm, float xscale, float yscale):filename(nm), xScale(xscale), yScale(yscale)
{}

cocos2d::Scene* SceneMaker::createScene()
{
    auto scene = Scene::create();
    auto layer = SceneMaker::create();
    scene->addChild(layer);
    return scene;
}

bool SceneMaker::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto bg = Sprite::create(filename);
    
    
    bg->setAnchorPoint(Vec2(0.5, 0.5));
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    bg->setScale(xScale, yScale);
    this->addChild(bg,1);
    
    return true;
    
}
