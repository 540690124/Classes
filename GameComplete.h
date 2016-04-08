#pragma once
#include "cocos2d.h"
USING_NS_CC;

class GameComplete:public Layer
{
public:
	static Scene * scene();
	virtual bool init();
	CREATE_FUNC(GameComplete);

	void menuCloseCallBack(Ref * pSender);//关闭按钮的回调函数
	
};

