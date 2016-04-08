#pragma once
#include "cocos2d.h"
USING_NS_CC;
//矿工方向
typedef enum 
{
	left = 0,
	right
}DirectionType;

class Miner:public Sprite
{
public:
	Miner(void);
	~Miner(void);
    //矿工执行动作
	void runMinerAction(DirectionType direction);
};

