#pragma once
#include "cocos2d.h"
#include "Miner.h"
#include "Hook.h"
#include "Tools.h"

using namespace cocos2d;

class GameLayer:public Layer
{
public:
	GameLayer(void);
	~GameLayer(void);

	static Scene * scene();
	virtual bool init();
	CREATE_FUNC(GameLayer);

	Miner * miner;//矿工对象
	Hook * hook;//钩子对象
	ItemUnits * theCatchItemUnit;//被钩中的物品对象


	Sprite * alarmClock;//闹钟精灵
	Label * alarmClockLabel;//时间标签
	Sprite * totalScoreSpr;//当前分数精灵
	Label * totalScoreLabel;//当前分数标签
	Sprite * levelNumSpr;//关卡数精灵
	Label * levelNumLabel;//关卡数标签
	Sprite * goalScoreSpr;//目标分数精灵
	Label * goalScoreLabel;//目标分数标签

	int currentTime;//当前剩余时间
	void TimeCounter();//倒计时器函数

	void onEnter()override;//进入场景时的回调函数
	void onExit()override;//退出场景时的回调函数
    
    //重载父类的触摸事件的回调函数
	virtual bool onTouchBegan(Touch *touch, Event *unused_event)override;//触摸开始
	virtual void onTouchMoved(Touch *touch, Event *unused_event)override;//触摸移动
	virtual void onTouchEnded(Touch *touch, Event *unused_event)override;//触摸结束
	virtual void onTouchCancelled(Touch *touch, Event *unused_event)override;//触摸取消

	void hookIsBack();//钩子是否返回的回调函数

	__Array * ItemArray;//保存物品的数组

	void addItem(); //添加物品的函数
    
    //按照类型和数量添加物品
	void addItemWithType(ItemQuaulityType type, int count);
    
    //添加精灵和标签
	void addSprAndLabel();
    
    //暂停按钮的回调函数
    //void onMenuPause(Ref * pSender);
    
	Menu * boomMenu;//炸弹按钮
	void usedBoom();//使用炸弹时的回调函数
	void remove(Node * sender, ItemUnits * item);//移除被炸毁的物品
	void removeSelf(Node * sender, Sprite * boom);//移除炸弹
	void stopMinerAction();//矿工停止动作的回调函数
	void boomSpecialEfficiency(Vec2 point);//炸弹播放特效的函数

	void checkUpHit();//碰撞检测

    //物品从数组中移除
	void deleteItemUnit(Node * sender,ItemUnits * item);
    //物品跟随钩子移动
	void itemUnitFollowHookFunc();
    
    //画线
    void draw_line();
    DrawNode * draw_node;//画线节点对象
};

