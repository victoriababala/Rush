
#include "FirstLevelScene.h"
#include "SimpleAudioEngine.h"
#include <GameOverScene.h>
#define TRANSITION_TIME 0.8
USING_NS_CC;

Scene* FirstLevelScene::createScene()
{
    return FirstLevelScene::create();
}

auto AudioLevel1 = CocosDenshion::SimpleAudioEngine::getInstance();

bool FirstLevelScene::init()
{
  
    if ( !Scene::init() )
    {
        return false;
    }

    schedule(CC_SCHEDULE_SELECTOR(FirstLevelScene::update));

    auto listener = EventListenerKeyboard::create();

    listener->onKeyPressed = CC_CALLBACK_2(FirstLevelScene::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(FirstLevelScene::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto BackgroundLevel1 = Sprite::create("level1background1.jpg");
    BackgroundLevel1->setAnchorPoint(Vec2(0.5, 0.5));
    BackgroundLevel1->setScale(1.5);
    BackgroundLevel1->setPosition(Vec2(visibleSize.width / 2 - 50, visibleSize.height / 2));
    this->addChild(BackgroundLevel1, 0);
    auto AnimationLevel1 = Animation::create();
    AnimationLevel1->addSpriteFrameWithFile("level1background1.jpg");
    AnimationLevel1->addSpriteFrameWithFile("level1background2.jpg");
    AnimationLevel1->setDelayPerUnit(1.0f);
    Animate* animate = Animate::create(AnimationLevel1);
    BackgroundLevel1->runAction(RepeatForever::create(animate));


    LivesIndicator = Sprite::create("3_livespicture.png");
    LivesIndicator->setPosition(Vec2(220, 850));
    LivesIndicator->setScale(0.7);
    this->addChild(LivesIndicator);

    PauseLabel = Label::createWithTTF("PAUSED", "fonts/ARCADECLASSIC.ttf", 120);
    PauseLabel->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2));
    PauseLabel->setColor(Color3B::BLACK);
    PauseLabel->setVisible(false);
    this->addChild(PauseLabel);
  

    CarLevel1 = Sprite::create("level1.car.png");
    CarLevel1->setPosition(Vec2(visibleSize.width / 2 + origin.x, 100));
   // CarLevel1->setScale(0.7);
    this->addChild(CarLevel1);

    ObstacleLevel1 = nullptr;

    lifesLabel = Label::createWithTTF("Lives  " + std::to_string(lives), "fonts/ARCADECLASSIC.ttf", 45);
    lifesLabel->setPosition(Vec2(100, 850));
    lifesLabel->setColor(Color3B::BLACK);
    this->addChild(lifesLabel);

    scoreLabel = Label::createWithTTF("Score  " + std::to_string(score), "fonts/ARCADECLASSIC.ttf", 50);
    scoreLabel->setPosition(Vec2(650, 850));
    scoreLabel->setColor(Color3B::BLACK);
    this->addChild(scoreLabel);
   

     pauseButton = MenuItemImage::create("pause_button.png", "pause_button.png", CC_CALLBACK_1(FirstLevelScene::PauseButtonClicked, this));
    pauseButton->setPosition(Point(350, 850));
    pauseButton->setScale(1.3);


    musicButton = MenuItemImage::create("musiconbutton.png", "musiconbutton.png", CC_CALLBACK_1(FirstLevelScene::MusicButtonClicked, this));
    musicButton->setPosition(Point(470, 855));
    musicButton->setScale(0.5);

    auto menu = Menu::create(pauseButton, musicButton, NULL);
    menu->setPosition(Point::ZERO);

    this->addChild(menu);

    elapsedTime = 0;

    return true;
}

void FirstLevelScene::update(float dt)
{
    Point p = CarLevel1->getPosition();

    if (p.x < 630) {
        if (go_r) CarLevel1->setPosition(Vec2(p.x + 10, p.y));
    }
    if (p.x > 120) {
        if (go_l) CarLevel1->setPosition(Vec2(p.x - 10, p.y));
    }
    elapsedTime += dt;

    if (elapsedTime >= 3.0f)
    {
        elapsedTime = 0;
        SpawnObstacle();
    }

    if (ObstacleLevel1)
    {
        float progress = elapsedTime / 3.0f;
        float scale = 0.2f + progress * (0.7f - 0.1f);

        if (BoolSpawnObstacleLeft)
        {
            Vec2 position = Vec2(380 - progress * 100, 280 - progress * 300);
            ObstacleLevel1->setScale(scale);
            ObstacleLevel1->setPosition(position);

        }
        else if (BoolSpawnObstacleRight)
        {
            Vec2 position = Vec2(400 + progress * 200, 280 - progress * 300);
            ObstacleLevel1->setScale(scale);
            ObstacleLevel1->setPosition(position);
        }
        
        if (checkCollision())
        {
           
            AudioLevel1->preloadEffect("hitsound.wav");
            AudioLevel1->playEffect("hitsound.wav");
            lives--;
            lifesLabel->setString("Lives  " + std::to_string(lives));

            if (lives == 0)
            {
                auto scene = GameOverScene::createScene(score);
                AudioLevel1->stopBackgroundMusic();

                AudioLevel1->preloadEffect("gameover.mp3");
                AudioLevel1->playEffect("gameover.mp3");
                LivesIndicator->setTexture("0_livespicture.png");
                /*Sleep(1500);*/
                Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
            }
            else if (lives == 2) LivesIndicator->setTexture("2_livespicture.png");
            else if (lives == 1) LivesIndicator->setTexture("1_livepicture.png");
            ObstacleLevel1->removeFromParentAndCleanup(true);
            ObstacleLevel1 = nullptr;
        }
        else 
        {
            score += 1;
            scoreLabel->setString("Score  " + std::to_string(score));
        }

    }
  
}
bool FirstLevelScene::checkCollision()
{
    Rect carRect = CarLevel1->getBoundingBox();
    Rect obstacleRect = ObstacleLevel1->getBoundingBox();

    if (carRect.intersectsRect(obstacleRect))
    {
        return true;
    }
    return false;
}
void FirstLevelScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if ((int)keyCode == 27) go_r = true;

    if ((int)keyCode == 26) go_l = true;
}

void FirstLevelScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if ((int)keyCode == 27) go_r = false;


    if ((int)keyCode == 26) go_l = false;
}

void FirstLevelScene::PauseButtonClicked(cocos2d::Ref* sender)
{
    if (!pause)
    {
        pauseButton->setColor(Color3B(43, 41, 36));
        PauseLabel->setVisible(true);
        Director::getInstance()->pause();

    }
    else
    {
        pauseButton->setColor(Color3B(255, 255, 255));
        PauseLabel->setVisible(false);
        Director::getInstance()->resume();
    }
    pause = !pause;
}

void FirstLevelScene::MusicButtonClicked(cocos2d::Ref* sender)
{
    if (playMusic)
    {
        AudioLevel1->resumeBackgroundMusic();
        musicButton->setColor(Color3B(255, 255, 255));
    }
    else
    {
        AudioLevel1->pauseBackgroundMusic();
        musicButton->setColor(Color3B(40, 41, 56));
    }
    playMusic = !playMusic;
}

void FirstLevelScene::SpawnObstacle()

{
    BoolSpawnObstacleLeft = BoolSpawnObstacleRight = false;
    int randomSprite = rand() % 3;  // Генерація випадкового числа від 0 до 2
    const char* spritePath;

    if (ObstacleLevel1)
    {
        ObstacleLevel1->removeFromParentAndCleanup(true);
        ObstacleLevel1 = nullptr;
    }

    switch (randomSprite)
    {
    case 0:
        spritePath = "palky1.png";
        break;
    case 1:
        spritePath = "tyres1.png";
        break;
    case 2:
        spritePath = "penyok.png";
        break;
    default:
        spritePath = "palky1.png";  // За замовчуванням
        break;
    }

    int randomBool = rand() % 2;  // Генерація випадкового числа від 0 до 2
    ObstacleLevel1 = Sprite::create(spritePath);

    ObstacleLevel1->setScale(0.1f);
    this->addChild(ObstacleLevel1);

    switch (randomBool)
    {
    case 0:
        BoolSpawnObstacleRight = true;
        ObstacleLevel1->setPosition(Vec2(400, 280));
        break;
    case 1:
        BoolSpawnObstacleLeft = true;
        ObstacleLevel1->setPosition(Vec2(380, 280));
        break;

    default:
        BoolSpawnObstacleRight = true;
        ObstacleLevel1->setPosition(Vec2(400, 280));
        break;
    }
}


