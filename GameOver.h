#pragma once
#include "cocos2d.h"
USING_NS_CC;

class GameOver:public Layer
{
public:
	static Scene * scene();
	virtual bool init();
	CREATE_FUNC(GameOver);

	void newCallBack();//新游戏按钮的回调函数
	void continueCallBack();//继续游戏的回调函数
	void exitCallBack();//退出游戏的回调函数
};

