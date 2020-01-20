//
//  GameOverScene.hpp
//  Pachikuri-mobile
//
//  Created by 佐々木勇星 on 2020/01/13.
//

#ifndef GameOverScene_hpp
#define GameOverScene_hpp

#include <stdio.h>
#include <cocos2d.h>

class GameOverScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    //ボタンを押した時の関数
    void pushAgain(Ref *pSender);
    void pushBack(Ref *pSender);
    
    CREATE_FUNC(GameOverScene);
};

#endif /* GameOverScene_hpp */
