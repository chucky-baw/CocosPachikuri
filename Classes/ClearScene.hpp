//
//  ClearScene.hpp
//  Pachikuri-mobile
//
//  Created by 佐々木勇星 on 2020/01/07.
//

#ifndef ClearScene_hpp
#define ClearScene_hpp

#include <stdio.h>
#include <cocos2d.h>

class ClearScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(ClearScene);

};

#endif /* ClearScene_hpp */
