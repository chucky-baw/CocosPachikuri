//
//  SceneMaker.hpp
//  Pachikuri-mobile
//
//  Created by 佐々木勇星 on 2020/01/13.
//

#ifndef SceneMaker_hpp
#define SceneMaker_hpp

#include <stdio.h>
#include <cocos2d.h>

class SceneMaker : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    
    std::string filename;
    float xScale, yScale;
    virtual bool init();
    //CREATE_FUNC(SceneMaker);
    
    
    SceneMaker(const std::string &nm, float xscale, float yscale);
    
};

#endif /* SceneMaker_hpp */
