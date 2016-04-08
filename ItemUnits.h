#pragma once
#include "cocos2d.h"
USING_NS_CC;
//物品的大小
typedef enum 
{
	Item_small = 0,
	Item_middle,
	Item_large
}ItemSizeType;
//物品的种类
typedef enum 
{
	Item_gold = 0,
	Item_stone,
	Item_diamond,
	Item_secret
}ItemQuaulityType;


class ItemUnits:public Sprite
{
public:
    //以种类和大小创建物品
	ItemUnits(ItemQuaulityType spriteType,ItemSizeType spriteSize);
	~ItemUnits(void);

	int weight;//物品重量
	int score;//物品分数
	bool isCatch;//物品是否被钩中的标识
};

