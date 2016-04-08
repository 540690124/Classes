#pragma once
#include "cocos2d.h"
USING_NS_CC;
class TradesWoman:public Sprite
{
public:
	TradesWoman(void);
	~TradesWoman(void);
	void action1();//售货员欢迎动作
	void action2();//售货员高兴动作
	void action3();//售货员不高兴动作
};

