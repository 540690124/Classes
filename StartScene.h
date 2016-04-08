#pragma once
#include "cocos2d.h"

USING_NS_CC;

class StartScene:public Layer
{
public:
	StartScene(void);
	~StartScene(void);
	
	static Scene * scene();
	virtual bool init();
	CREATE_FUNC(StartScene);

	void start();//开始按钮的回调函数

	bool isMusicOff;//音乐是否播放的flag（标识）
	void music();//音乐开关按钮的回调函数
};

