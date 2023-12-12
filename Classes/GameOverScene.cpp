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

#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include <ChooseLevelScene.h>
#include <Definitions.h>
#include <MenuScene.h>

USING_NS_CC;
int score = 0;
auto audioGameOverScene = CocosDenshion::SimpleAudioEngine::getInstance();
Scene* GameOverScene::createScene(int p)
{
    score = p;
    return GameOverScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("gameoverbackground.jpeg");
    background->setAnchorPoint(Vec2(0.5, 0.5));
    background->setScaleX(visibleSize.width / background->getContentSize().width);
    background->setScaleY(visibleSize.height / background->getContentSize().height);
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    auto TryAgainButton = MenuItemImage::create("continue.png", "continue.png", CC_CALLBACK_1(GameOverScene::RestartButtonClicked, this));
    TryAgainButton->setPosition(Point(visibleSize.width/2, visibleSize.height / 2 ));
    TryAgainButton->setOpacity(0);
    TryAgainButton->setScale(1.6);

    auto  RestartLabel = Label::createWithTTF("RESTART", "fonts/ARCADECLASSIC.ttf", 120);
    RestartLabel->setPosition(Vec2(visibleSize.width / 2 +10, visibleSize.height / 2));
    RestartLabel->setColor(Color3B::WHITE);
    RestartLabel->enableShadow(Color4B::BLACK);
    RestartLabel->enableOutline(Color4B::BLACK, 4);
    this->addChild(RestartLabel,1);

    auto  MainMenuLabel = Label::createWithTTF("Main Menu", "fonts/ARCADECLASSIC.ttf",40);
    MainMenuLabel->setPosition(Point(110, visibleSize.height - 30));
    MainMenuLabel->setColor(Color3B::WHITE);
    MainMenuLabel->enableShadow(Color4B::BLACK);
    MainMenuLabel->enableOutline(Color4B::BLACK, 4);
    this->addChild(MainMenuLabel, 1);

    auto MainMenuButton = MenuItemImage::create("continue.png", "continue.png", CC_CALLBACK_1(GameOverScene::MainMenuButtonClicked, this));
    MainMenuButton->setPosition(Point(110, visibleSize.height - 30));
    MainMenuButton->setOpacity(0);
    MainMenuButton->setScaleX(0.8);
    MainMenuButton->setScaleY(0.4);

    auto  ScoreLabel = Label::createWithTTF("SCORE  " + std::to_string(score), "fonts/ARCADECLASSIC.ttf", 80);
    ScoreLabel->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2 + 200));
    ScoreLabel->setColor(Color3B::WHITE);
    ScoreLabel->enableShadow(Color4B::BLACK);
    ScoreLabel->enableOutline(Color4B::BLACK, 4);
    this->addChild(ScoreLabel, 1);

    auto ExitButton = MenuItemImage::create("powerbutton.png", "powerbutton.png", CC_CALLBACK_1(GameOverScene::ExitButtonClicked, this));
    ExitButton->setPosition(Point(750, visibleSize.height - 850));
    ExitButton->setScale(0.3);

    auto menu = Menu::create(MainMenuButton, TryAgainButton, ExitButton, NULL);
    menu->setPosition(Point::ZERO);

    this->addChild(menu,1);

    this->addChild(background, 0);

    return true;
}

void GameOverScene::RestartButtonClicked(cocos2d::Ref* sender)
{
    auto scene = ChooseLevelScene::createScene();
    audioGameOverScene->preloadEffect("click.wav");
    audioGameOverScene->playEffect("click.wav");
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void GameOverScene::MainMenuButtonClicked(cocos2d::Ref* sender)
{
    auto scene = MenuScene::createScene(true);
    audioGameOverScene->preloadEffect("click.wav");
    audioGameOverScene->playEffect("click.wav");
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void GameOverScene::ExitButtonClicked(cocos2d::Ref* sender)
{
    audioGameOverScene->preloadEffect("click.wav");
    audioGameOverScene->playEffect("click.wav");
    Sleep(500);
    exit(1);
}

