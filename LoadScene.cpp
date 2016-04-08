//
//  LoadScene.cpp
//  GoldMiner
//
//  Created by WF on 15/11/16.
//
//

#include "LoadScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
Scene * LoadScene::scene()
{
    auto scene=Scene::create();
    auto layer=LoadScene::create();
    scene->addChild(layer);
    
    return scene;
}
bool LoadScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    //获取屏幕尺寸
    Size winSize=Director::getInstance()->getWinSize();
    
    //背景
    auto bg=Sprite::create("bg.png");
    bg->setPosition(Vec2(winSize.width/2,winSize.height/2));
    addChild(bg);
    
    //播放背景音乐
    SimpleAudioEngine::getInstance()->playBackgroundMusic("backMusic.mp3",true);
    
    //加载进度条
    /********创建进度条背景*****************/
    auto proBG=Sprite::create("loading_progress_bg.png");
    proBG->setPosition(winSize.width/2,winSize.height/6);
    addChild(proBG);
    /********创建进度条************/
    auto proBar=Sprite::create("loading_progress_bar.png");
    auto progress=ProgressTimer::create(proBar);
    progress->setType(ProgressTimer::Type::BAR);
    progress->setPosition(winSize.width/2,winSize.height/6+1);
    progress->setBarChangeRate(Vec2(1,0));
    progress->setMidpoint(Vec2(0,1));
    addChild(progress);
    /********创建进度条动作**********/
    auto progressTo=ProgressFromTo::create(4.0f, 0, 100);
    auto seq=Sequence::create(progressTo,CallFunc::create(this,callfunc_selector(LoadScene::createClick)), NULL);
    progress->runAction(seq);//进度条执行这个动作
    
    
    
    return true;
}
void LoadScene::LoadResource()
{
    int count = 0;

    
}
void LoadScene::createClick()
{
    //创建 click按钮
    auto menuImage=MenuItemImage::create("clickFont.png","clickFont.png");
    menuImage->setCallback(CC_CALLBACK_0(LoadScene::click, this));
    auto menu=Menu::create(menuImage,NULL);
    menu->setPosition(Vec2(Director::getInstance()->getWinSize().width/2,Director::getInstance()->getWinSize().height/6+30));
    this->addChild(menu);
}
void LoadScene::click()
{
    log("click!!!");
    //点击按钮，播放音效
    SimpleAudioEngine::getInstance()->playEffect("MP3_NORMAL.mp3");
    auto scene=StartScene::scene();
    Director::getInstance()->replaceScene(scene);
}







