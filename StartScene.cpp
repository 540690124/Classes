#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"
using namespace CocosDenshion;


StartScene::StartScene(void)
{
}


StartScene::~StartScene(void)
{
}

Scene * StartScene::scene()
{
	auto scene =  Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);

	return scene;
}

bool StartScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
    //获取屏幕尺寸
	auto winSize = Director::getInstance()->getWinSize();
    
    //添加背景
	auto bg = Sprite::create("MainMenu.png");
	bg->setPosition(Vec2(winSize.width/2,winSize.height/2));
	addChild(bg);

	//添加开始按钮
	auto item = MenuItemImage::create("PlayMenu.png","PlayMenu.png");
    //设置开始按钮的回调函数
	item->setCallback(CC_CALLBACK_0(StartScene::start,this));
	auto startMenu = Menu::create(item,NULL);
	startMenu->setPosition(Vec2(130,225));//给按钮设置位置

	addChild(startMenu);

	//播放背景音乐 true表示循环播放
	SimpleAudioEngine::getInstance()->playBackgroundMusic("backMusic.mp3",true);
    
    //音乐标识初始化为播放
	isMusicOff = false;
    
    //创建音乐开关按钮
	auto item1 = MenuItemImage::create("soundController.png","soundController.png");
	auto item2 = MenuItemImage::create("soundController2.png","soundController2.png");
    //设置音乐开关按钮的回调函数
	auto musicItem = MenuItemToggle::createWithCallback(CC_CALLBACK_0(StartScene::music,this),item1,item2,NULL);
	auto musicMenu = Menu::create(musicItem,NULL);
	musicMenu->setPosition(Vec2(50,50));
	addChild(musicMenu);

	return true;
}

void StartScene::start()
{
	log("start");
	//点击开始按钮，进入游戏场景
	Director::getInstance()->replaceScene(TransitionPageTurn::create(1.0f,GameLayer::scene(),false));
}

void StartScene::music()
{
	if (isMusicOff)//如果音乐没有播放
	{
        //播放音乐
		SimpleAudioEngine::getInstance()->playBackgroundMusic("backMusic.mp3",true);
		isMusicOff = false;//音乐标识置为播放状态
	}
	else//当音乐正在播放
	{
        //停止背景音乐
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		isMusicOff = true;//音乐标识置为未播放状态
	}
}
