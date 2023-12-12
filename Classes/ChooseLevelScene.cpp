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

#include "ChooseLevelScene.h"
#include "SimpleAudioEngine.h"
#include <FirstLevelScene.h>
#include <SecondLevelScene.h>
#include <ThirdLevelScene.h>
#include <AudioEngine.h>
#include <InstructionScene.h>
#define TRANSITION_TIME 0.5
USING_NS_CC;

Scene* ChooseLevelScene::createScene()
{
    return ChooseLevelScene::create();
}

auto audio1 = CocosDenshion::SimpleAudioEngine::getInstance();

// on "init" you need to initialize your instance
bool ChooseLevelScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("chooseback.jpeg");
    background->setAnchorPoint(Vec2(0.5, 0.5));
    background->setScaleX(visibleSize.width / background->getContentSize().width);
    background->setScaleY(visibleSize.height / background->getContentSize().height);
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    auto TextLabel = Label::createWithTTF("Choose a  level", "fonts/ARCADECLASSIC.ttf", 100);
    TextLabel->setPosition(Vec2(Point(visibleSize.width / 2 + origin.x , visibleSize.height / 2 + origin.y + 300)));
    TextLabel->setColor(Color3B::WHITE);
    TextLabel->enableShadow(Color4B::BLACK);
    TextLabel->enableOutline(Color4B::RED, 4);
    this->addChild(TextLabel,1);
   
    this->addChild(background, 0);

    auto BackToInstructions = MenuItemImage::create("backbutton.png", "backbutton.png", CC_CALLBACK_1(ChooseLevelScene::goToInstructionScene, this));
    BackToInstructions->setPosition(Point(70, visibleSize.height - 50));
    BackToInstructions->setScale(1.2);

    auto FirstLevel = MenuItemImage::create("level1.png", "level1.png", CC_CALLBACK_1(ChooseLevelScene::GoToFirstLevelScene, this));
    FirstLevel->setPosition(Point(visibleSize.width / 2 + origin.x -10, visibleSize.height / 2 + origin.y +150 ));
    FirstLevel->setScale(1.5);
    auto SecondLevel = MenuItemImage::create("level2.png", "level2.png", CC_CALLBACK_1(ChooseLevelScene::GoToSecondLevelScene, this));
    SecondLevel->setPosition(Point((visibleSize.width / 2) + origin.x, visibleSize.height / 2 -30 + origin.y));
    SecondLevel->setScale(1.5);
    auto ThirdLevel = MenuItemImage::create("level3.png", "level3.png", CC_CALLBACK_1(ChooseLevelScene::GoToThirdLevelScene, this));
    ThirdLevel->setPosition(Point((visibleSize.width / 2) + origin.x, visibleSize.height / 2 - 220 + origin.y));
    ThirdLevel->setScale(1.5);
    auto menu = Menu::create(BackToInstructions, FirstLevel, SecondLevel, ThirdLevel , NULL);
    menu->setPosition(Point::ZERO);

    this->addChild(menu);
    return true;
}
void ChooseLevelScene::GoToFirstLevelScene(cocos2d::Ref* sender)
{
    auto scene = FirstLevelScene::createScene();
    audio1->preloadEffect("click.wav");
    audio1->playEffect("click.wav");
    audio1->playBackgroundMusic("level1backgroundsong.mp3", true);
   
   
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
void ChooseLevelScene::GoToSecondLevelScene(cocos2d::Ref* sender)
{
    auto scene = SecondLevelScene::createScene();
    audio1->preloadEffect("click.wav");
    audio1->playEffect("click.wav");
    audio1->playBackgroundMusic("level2backgroundsong.mp3", true);
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
void ChooseLevelScene::GoToThirdLevelScene(cocos2d::Ref* sender)
{
    auto scene = ThirdLevelScene::createScene();
    audio1->preloadEffect("click.wav");
    audio1->playEffect("click.wav");
    audio1->playBackgroundMusic("level3backgroundsong.mp3",true);
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void ChooseLevelScene::goToInstructionScene(Ref* pSender)
{
    auto scene = InstructionScene::createScene();
    audio1->preloadEffect("click.wav");
    audio1->playEffect("click.wav");
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

