#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Hook:public Sprite
{
public:
	Hook(void);
	~Hook(void);

	//钩子是否钩中物品的标识
	bool isCatchItem;
	//钩子是否收回的标识
	bool isBack;
	//钩子摆动动作的函数
	void runRotate();
	//计算钩子最远位置的函数
	void runToPoint(Point p);
	//钩子收回的回调函数
	void runBack();
	//钩子逻辑函数
	void runTarget();
};

