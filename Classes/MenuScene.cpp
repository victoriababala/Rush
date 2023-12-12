/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include <ChooseLevelScene.h>
#include <Settings.h>
#include <InstructionScene.h>
#include <AudioEngine.h>
#include <Definitions.h>
USING_NS_CC;
bool playbackmusic;
auto audioMenuScene = CocosDenshion::SimpleAudioEngine::getInstance();
Scene* MenuScene::createScene(bool p)
{
    playbackmusic = p;
    return MenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

 
    if (playbackmusic)
    {
        audioMenuScene->preloadBackgroundMusic("backgroundsong.mp3");
        audioMenuScene->playBackgroundMusic("backgroundsong.mp3");
    }
   

    auto background = Sprite::create("main_background.jpeg");
    background->setAnchorPoint(Vec2(0.5, 0.5));
    background->setScale(1.5);
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background,0);

    auto playItem = MenuItemImage::create("ssttbbb.png", "ssttbbb.png", CC_CALLBACK_1(MenuScene::GoToChooseLevelScene, this));
    playItem->setPosition(Point(visibleSize.width / 2 , visibleSize.height / 2 -100 ));
    playItem->setScale(1.7);

    auto settingsItem = MenuItemImage::create("infobutton.png", "infobutton.png", CC_CALLBACK_1(MenuScene::GoToSettings, this));
    settingsItem->setPosition(Point(750, visibleSize.height  - 50  ));
    settingsItem->setScale(0.5);

    auto powerItem = MenuItemImage::create("powerbutton.png", "powerbutton.png", CC_CALLBACK_1(MenuScene::ExitButtonClicked, this));
    powerItem->setPosition(Point(750, visibleSize.height - 850));
    powerItem->setScale(0.3);

    musicButton = MenuItemImage::create("musiconbutton.png", "musiconbutton.png", CC_CALLBACK_1(MenuScene::MusicButtonClicked, this));
    musicButton->setPosition(Point(50, 850));
    musicButton->setScale(0.7);
    auto menu = Menu::create(musicButton,playItem, settingsItem, powerItem, NULL);
    menu->setPosition(Point::ZERO);

    this->addChild(menu);
  
    return true;
}
void MenuScene::MusicButtonClicked(cocos2d::Ref* sender)
{
    if (playMusic)
    {
        audioMenuScene->resumeBackgroundMusic();
        audioMenuScene->preloadEffect("click.wav");
        audioMenuScene->playEffect("click.wav");
    }
    else
    {
        audioMenuScene->pauseBackgroundMusic();
        audioMenuScene->preloadEffect("click.wav");
        audioMenuScene->playEffect("click.wav");
    }
    playMusic = !playMusic;
}
void MenuScene::GoToChooseLevelScene(cocos2d::Ref* sender)
{
    auto scene = InstructionScene::createScene();
    audioMenuScene->preloadEffect("click.wav");
    audioMenuScene->playEffect("click.wav");
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
void MenuScene::GoToSettings(cocos2d::Ref* sender)
{
    auto scene =Settings::createScene();
    audioMenuScene->preloadEffect("click.wav");
    audioMenuScene->playEffect("click.wav");
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void MenuScene::ExitButtonClicked(cocos2d::Ref* sender)
{
    audioMenuScene->preloadEffect("click.wav");
    audioMenuScene->playEffect("click.wav");
    Sleep(500);
    exit(1);
}


