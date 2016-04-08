//
//  LoadScene.h
//  GoldMiner
//
//  Created by WF on 15/11/16.
//
//

#ifndef __GoldMiner__LoadScene__
#define __GoldMiner__LoadScene__

#include <stdio.h>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"//包含音乐播放引擎头文件
#include "StartScene.h"
using namespace CocosDenshion;

USING_NS_CC;

class LoadScene:public Layer
{
public:
    static Scene * scene();
    virtual bool init();
    CREATE_FUNC(LoadScene);
    
    void LoadResource();
    void createClick();//创建跳过按钮
    void click();//跳过按钮的回调函数
};

#endif /* defined(__GoldMiner__LoadScene__) */
