

#include "Settings.h"
#include "SimpleAudioEngine.h"
#include <MenuScene.h>
#include <AudioEngine.h>
#include <Definitions.h>
USING_NS_CC;

auto audioSettings   = CocosDenshion::SimpleAudioEngine::getInstance();
Scene* Settings::createScene()
{
    return Settings::create();
}

// Print useful error message instead of segfaulting when files are not there.


// on "init" you need to initialize your instance
bool Settings::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize    = Director::getInstance()->getVisibleSize();
    Vec2 origin  = Director::getInstance()->getVisibleOrigin();

    auto background  = Sprite::create("infobackground.png");
    background->setAnchorPoint(Vec2(0.5, 0.5));
    background->setScaleX(visibleSize.width / background->getContentSize().width);
    background->setScaleY(visibleSize.height / background->getContentSize().height);
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(background, 0);

    department_button_->setPosition(Point(680, visibleSize.height - 100));
    department_button_->setScale(1.1f);
    department_button_->addTouchEventListener(CC_CALLBACK_2(Settings::departmentButtonClicked, this));
    this->addChild(department_button_);

    gameHub_button_->setPosition(Vec2(120, 120));
    gameHub_button_->setScale(1.2f);
    gameHub_button_->addTouchEventListener(CC_CALLBACK_2(Settings::gameHubButtonClicked, this));
    this->addChild(gameHub_button_);


    auto backtomenu = MenuItemImage::create("backbutton.png", "backbutton.png", CC_CALLBACK_1(Settings::goToMenuScene, this));
    backtomenu->setPosition(Point(70, visibleSize.height - 50));
    backtomenu->setScale(1.3);

    auto menu  = Menu::create( backtomenu, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    return true;
}

void Settings::departmentButtonClicked(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == ui::Widget::TouchEventType::ENDED)
    {
        audioSettings->preloadEffect("click.wav");
        audioSettings->playEffect("click.wav");
        Application::getInstance()->openURL("https://comp-sc.pnu.edu.ua/");
    } 
}

void Settings::gameHubButtonClicked(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type == ui::Widget::TouchEventType::ENDED)
    {
        audioSettings->preloadEffect("click.wav");
        audioSettings->playEffect("click.wav");
        Application::getInstance()->openURL("https://comp-sc.pnu.edu.ua/gamehubpnu/");
    }
}

void Settings::goToMenuScene(Ref* pSender)
{
    auto scene = MenuScene::createScene(false);
    audioSettings->preloadEffect("click.wav");
    audioSettings->playEffect("click.wav");
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}



