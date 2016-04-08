//
//  MainLayer.h
//  GoldMiner3.0
//
//  Created by WF on 15/12/23.
//
//

#ifndef __GoldMiner3_0__MainLayer__
#define __GoldMiner3_0__MainLayer__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class MainLayer:public Layer
{
public:
    CREATE_FUNC(MainLayer);
    virtual bool init();
private:
    void onMenuClick(Ref * pSender);
};
#endif /* defined(__GoldMiner3_0__MainLayer__) */
