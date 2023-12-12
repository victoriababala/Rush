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

#include "InstructionScene.h"
#include "SimpleAudioEngine.h"
#include <FirstLevelScene.h>
#include <SecondLevelScene.h>
#include <ThirdLevelScene.h>
#include <ChooseLevelScene.h>
#include <MenuScene.h>
#define TRANSITION_TIME 0.5
USING_NS_CC;
auto audioInsctructionScene = CocosDenshion::SimpleAudioEngine::getInstance();
Scene* InstructionScene::createScene()
{
    return InstructionScene::create();
}



// on "init" you need to initialize your instance
bool InstructionScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto background = Sprite::create("instbc.png");
    background->setAnchorPoint(Vec2(0.5, 0.5));
    background->setScaleX(visibleSize.width / background->getContentSize().width);
    background->setScaleY(visibleSize.height / background->getContentSize().height);
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background, 0);

    auto backtomenu = MenuItemImage::create("backbutton.png", "backbutton.png", CC_CALLBACK_1(InstructionScene::goToMenuScene, this));
    backtomenu->setPosition(Point(70, visibleSize.height - 50));
    backtomenu->setScale(1.2);

    auto menu = Menu::create(backtomenu, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);

    auto listener = EventListenerKeyboard::create();

    listener->onKeyPressed = CC_CALLBACK_2(InstructionScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}
void InstructionScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    auto scene = ChooseLevelScene::createScene();
    audioInsctructionScene->preloadEffect("click.wav");
    audioInsctructionScene->playEffect("click.wav");
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void InstructionScene::goToMenuScene(Ref* pSender)
{
    auto scene = MenuScene::createScene(false);

    audioInsctructionScene->preloadEffect("click.wav");
    audioInsctructionScene->playEffect("click.wav");
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}


