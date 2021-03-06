#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "StartScene.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "GameOver.h"
#include "GameComplete.h"
#include "ShopLayer.h"
#include "LoadScene.h"
USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    //屏幕适配 宽480 高320 适配策略为自适应
	glview->setDesignResolutionSize(480,320,ResolutionPolicy::EXACT_FIT);
    //将音乐文件加载到缓存中
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("backMusic.mp3");
    
    //将帧动画资源加载到精灵帧缓存中
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Beautiful.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("minerAction.plist");
	
    // create a scene. it's an autorelease object
    auto scene = LoadScene::scene();
    
    //
    
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
