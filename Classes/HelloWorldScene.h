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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <vector>
USING_NS_CC;
class HelloWorld : public cocos2d::Scene
{
private:
    bool transitionFade = true;
    
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    HelloWorld();
    ~HelloWorld();
    
    void VelUpdate(float dt);
    void TimeUpdate(float dt);

    
    int trashCount = 0;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void clearMove();
    void gameOverMove();
    bool OnTouchBegan(cocos2d:: Touch* touch, cocos2d::Event* event);
    void OnTouchEnded(cocos2d:: Touch* touch, cocos2d::Event* event);
    bool _OnContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve);
    bool catCollision(PhysicsContact& contact);
    Sprite* addNewWall(Node *parent, Vec2 p, float widthScale, float heightScale, bool dynamic, const char *fileName);
    Sprite* addNewTrash(Node *parent, Vec2 v, bool dynamic, const char *fileName);
    
    Vec2 startPos;
    Vec2 endPos;
    Vec2 Direction;
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    //外部から呼び出すことができ，内部の変数を書き換えることができる関数を作成
    //残り時間の変数とラベル
    CC_SYNTHESIZE(float, _second, Second);
    CC_SYNTHESIZE_RETAIN(cocos2d::Label *, _secondLabel, SecondLabel);
    
};

#endif // __HELLOWORLD_SCENE_H__
