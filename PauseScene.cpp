//
//  PauseScene.cpp
//  GoldMiner3.0
//
//  Created by WF on 15/12/22.
//
//

#include "PauseScene.h"
#include "StartScene.h"
#include "GameLayer.h"
extern int TotalScore;
//传入一个CCrenderTexture
//相当于一个正在运行的游戏的截图作为这个暂停对话框的背景
//这样就看起来像是对话框在游戏界面之上，一般游戏当中都是这样子写的
Scene * PauseScene::scene(RenderTexture * sqr)
{
    auto scene = Scene::create();
    PauseScene * layer = PauseScene::create();
    scene->addChild(layer, 1);//把游戏层放上面，我们还要在这上面放按钮
    
    //使用gamescene界面中的截图纹理sqr创建Sprite
    //将其添加到PauseScene场景层中
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto back_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
    back_spr->setPosition(visibleSize.width/2,visibleSize.height/2);//位置为屏幕中心
    back_spr->setFlippedY(true);//翻转，因为UI坐标和OpenGL坐标不同
    back_spr->setColor(Color3B::GRAY);//图片颜色为灰色
    scene->addChild(back_spr);
    
    //添加游戏暂停背景小图，用来放按钮
    auto back_small_spr = Sprite::create("back_pause.png");
    back_small_spr->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    scene->addChild(back_small_spr);
    
    return scene;
}
bool PauseScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    //窗口大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //原点坐标
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //继续游戏按钮
    auto pContinueItem = MenuItemImage::create("pause_continue.png", "pause_continue.png",CC_CALLBACK_1(PauseScene::menuContinueCallBack, this));
    pContinueItem->setPosition(visibleSize.width/2, visibleSize.height/2+30);
    //重新开始按钮
    auto pRestartItem = MenuItemImage::create("pause_restart.png","pause_restart.png",CC_CALLBACK_1(PauseScene::menuRestart, this));
    pRestartItem->setPosition(visibleSize.width/2, visibleSize.height/2-20);
    //回主界面按钮
    auto pLoginItem = MenuItemImage::create("pause_login.png","pause_login.png",CC_CALLBACK_1(PauseScene::menuLogin, this));
    pLoginItem->setPosition(visibleSize.width/2, visibleSize.height/2-70);
    
    auto pMenu = Menu::create(pContinueItem,pRestartItem,pLoginItem, NULL);
    pMenu->setPosition(Vec2::ZERO);
    
    this->addChild(pMenu,2);
    
    return true;
}
void PauseScene::onEnter()
{
    Layer::onEnter();
}
void PauseScene::onExit()
{
    Layer::onExit();
}
//继续游戏
void PauseScene::menuContinueCallBack(Ref* s)
{
    log("continue");
    Director::getInstance()->popScene();
}
//重新开始游戏
void PauseScene::menuRestart(Ref* s)
{
    log("restart");
    TotalScore=100;
    Director::getInstance()->replaceScene(GameLayer::scene());
}
//回主界面
void PauseScene::menuLogin(Ref* s)
{
    log("login");
    Director::getInstance()->replaceScene(StartScene::scene());
}