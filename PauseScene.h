//
//  PauseScene.h
//  GoldMiner3.0
//
//  Created by WF on 15/12/22.
//
//

#ifndef __GoldMiner3_0__PauseScene__
#define __GoldMiner3_0__PauseScene__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class PauseScene:public Layer
{
public:
    static Scene * scene(RenderTexture * sqr);
    virtual bool init();
    CREATE_FUNC(PauseScene);
    
    void onEnter()override;
    void onExit()override;
    //继续游戏
    void menuContinueCallBack(Ref* s);
    //重新开始游戏
    void menuRestart(Ref*);
    //回主界面
    void menuLogin(Ref*);
};

#endif /* defined(__GoldMiner3_0__PauseScene__) */
