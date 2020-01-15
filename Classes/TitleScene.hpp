//
//  TitleScene.hpp
//  Pachikuri-mobile
//
//  Created by 佐々木勇星 on 2020/01/15.
//

#ifndef TitleScene_hpp
#define TitleScene_hpp

#include <stdio.h>
#include <cocos2d.h>

class TitleScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    //シーン遷移のためのタップ
    //bool OnTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    CREATE_FUNC(TitleScene);
};

#endif /* TitleScene_hpp */
