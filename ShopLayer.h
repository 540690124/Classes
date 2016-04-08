#pragma once
#include "cocos2d.h"
#include "TradesWoman.h"

USING_NS_CC;

class ShopLayer:public Layer
{
public:
	ShopLayer(void);
	~ShopLayer(void);

	static Scene * scene();
	virtual bool init();
	CREATE_FUNC(ShopLayer);

	Label * howMuch;//商品价格标签

	__Array * itemArray;//保存商品的数组
	__Array * messageArray;//保存商品信息的数组
	std::vector<Sprite *> itemVec;
	std::vector<Sprite *> informationVec;

	TradesWoman * npc;//售货员对象

	int selectItemNumber;//选择商品的索引
	void leftBtnFunc();//左选按钮的回调函数
	void rightBtnFunc();//右选按钮的回调函数
	void buyBtnFunc();//购买按钮的回调函数

	void goNext();//选择按钮的回调函数
	void npcAnger();//售货员生气的回调函数
	void gotoNextGame();//下一关按钮的回调函数

	bool isbuy;//是否购买的标识
};

