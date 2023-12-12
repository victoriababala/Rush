
#include "SecondLevelScene.h"
#include "SimpleAudioEngine.h"
#include <GameOverScene.h>
#define TRANSITION_TIME 0.8

USING_NS_CC;

Scene* SecondLevelScene::createScene()
{
    return SecondLevelScene::create();
}

auto AudioLevel2 = CocosDenshion::SimpleAudioEngine::getInstance();


bool SecondLevelScene::init()
{
   
    if ( !Scene::init() )
    {
        return false;
    }
    schedule(CC_SCHEDULE_SELECTOR(SecondLevelScene::update));

    auto listener = EventListenerKeyboard::create();

    listener->onKeyPressed = CC_CALLBACK_2(SecondLevelScene::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(SecondLevelScene::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto BackgroundLevel2 = Sprite::create("backlevel2.1.jpg");
    BackgroundLevel2->setAnchorPoint(Vec2(0.5, 0.5));
    BackgroundLevel2->setScale(1.5);
    BackgroundLevel2->setPosition(Vec2(visibleSize.width / 2 - 50, visibleSize.height / 2));
    this->addChild(BackgroundLevel2, 0);
    auto AnimationLevel2 = Animation::create();
    AnimationLevel2->addSpriteFrameWithFile("backlevel2.1.jpg");
    AnimationLevel2->addSpriteFrameWithFile("backlevel2.2.jpg");
    AnimationLevel2->setDelayPerUnit(1.0f);
    Animate* animate = Animate::create(AnimationLevel2);
    BackgroundLevel2->runAction(RepeatForever::create(animate));


    LivesIndicator = Sprite::create("3_livespicture.png");
    LivesIndicator->setPosition(Vec2(220, 850));
    LivesIndicator->setScale(0.7);
    this->addChild(LivesIndicator);

    PauseLabel = Label::createWithTTF("PAUSED", "fonts/ARCADECLASSIC.ttf", 120);
    PauseLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    PauseLabel->setColor(Color3B::BLACK);
    PauseLabel->setVisible(false);
    this->addChild(PauseLabel);


    CarLevel2 = Sprite::create("level2car.png");
    CarLevel2->setPosition(Vec2(visibleSize.width / 2 + origin.x, 70));
    CarLevel2->setScale(0.7);
    this->addChild(CarLevel2);

    Skorpio = Sprite::create("skorpio.png");
    
    Skorpio->setScale(0.2);
    this->addChild(Skorpio);
    float progress1 = elapsedTime / 2.7f;
   

    Vec2 position1 = Vec2(300 - progress1 * 1100, 230);
    Skorpio->setPosition(position1);

    ObstacleLevel2 = nullptr;

    lifesLabel = Label::createWithTTF("Lives  " + std::to_string(lives), "fonts/ARCADECLASSIC.ttf", 45);
    lifesLabel->setPosition(Vec2(100, 850));
    lifesLabel->setColor(Color3B::BLACK);
    this->addChild(lifesLabel);

    scoreLabel = Label::createWithTTF("Score  " + std::to_string(score), "fonts/ARCADECLASSIC.ttf", 50);
    scoreLabel->setPosition(Vec2(650, 850));
    scoreLabel->setColor(Color3B::BLACK);
    this->addChild(scoreLabel);


    pauseButton = MenuItemImage::create("pause_button.png", "pause_button.png", CC_CALLBACK_1(SecondLevelScene::PauseButtonClicked, this));
    pauseButton->setPosition(Point(350, 850));
    pauseButton->setScale(1.3);


    musicButton = MenuItemImage::create("musiconbutton.png", "musiconbutton.png", CC_CALLBACK_1(SecondLevelScene::MusicButtonClicked, this));
    musicButton->setPosition(Point(470, 855));
    musicButton->setScale(0.5);

    auto menu = Menu::create(pauseButton, musicButton, NULL);
    menu->setPosition(Point::ZERO);

    this->addChild(menu);

    elapsedTime = 0;
    
    return true;
}

void SecondLevelScene::update(float dt)
{
    Point p = CarLevel2->getPosition();

    if (p.x < 630) {
        if (go_r) CarLevel2->setPosition(Vec2(p.x + 5, p.y));
    }
    if (p.x > 120) {
        if (go_l) CarLevel2->setPosition(Vec2(p.x - 5, p.y));
    }
    elapsedTime += dt;

    if (elapsedTime >= 2.7f)
    {
        elapsedTime = 0;
        SpawnObstacleLevel2();
        SpawnBackgroundLevel2();
    }

    if (ObstacleLevel2)
    {
        float progress = elapsedTime / 2.7f;
        float scale = 0.1f + progress * (0.8f - 0.1f);

        Vec2 position1 = Vec2(300 - progress * 1100, 230);
        Skorpio->setPosition(position1);

        if (BoolSpawnObstacleLeftLvl2)
        {
            Vec2 position = Vec2(330 - progress * 100, 260 - progress * 300);
            ObstacleLevel2->setScale(scale);
            ObstacleLevel2->setPosition(position);

        }
        else if (BoolSpawnObstacleRightLvl2)
        {
            Vec2 position = Vec2(340 + progress * 200, 260 - progress * 300);
            ObstacleLevel2->setScale(scale);
            ObstacleLevel2->setPosition(position);
        }

        if (checkCollision())
        {

            AudioLevel2->preloadEffect("hitsound.wav");
            AudioLevel2->playEffect("hitsound.wav");
            lives--;
            lifesLabel->setString("Lives  " + std::to_string(lives));

            if (lives == 0)
            {
                auto scene = GameOverScene::createScene(score);
                AudioLevel2->stopBackgroundMusic();

                AudioLevel2->preloadEffect("gameover.mp3");
                AudioLevel2->playEffect("gameover.mp3");
                LivesIndicator->setTexture("0_livespicture.png");
                /*Sleep(1500);*/
                Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
            }
            else if (lives == 2) LivesIndicator->setTexture("2_livespicture.png");
            else if (lives == 1) LivesIndicator->setTexture("1_livepicture.png");
            ObstacleLevel2->removeFromParentAndCleanup(true);
            ObstacleLevel2 = nullptr;
        }
        else
        {
            score += 1;
            scoreLabel->setString("Score  " + std::to_string(score));
        }

        if (GroundLeftLevel2 && BoolSpawnGroundLeftLvl2)
        {
            float progress = elapsedTime / 2.0f;
            float scale = 0.2f + progress * (0.5f - 0.1f);


            Vec2 position = Vec2(300 - progress * 300, 260 - progress * 90);
            GroundLeftLevel2->setScale(scale);
            GroundLeftLevel2->setPosition(position);




        }
        if (GroundRightLevel2 && BoolSpawnGroundRightLvl2)
        {
            float progress = elapsedTime / 2.0f;
            float scale = 0.2f + progress * (0.5f - 0.1f);


            Vec2 position = Vec2(350 + progress * 350, 260 - progress * 90);
            GroundRightLevel2->setScale(scale);
            GroundRightLevel2->setPosition(position);

        }

    }

}
bool SecondLevelScene::checkCollision()
{
    Rect carRect = CarLevel2->getBoundingBox();
    Rect obstacleRect = ObstacleLevel2->getBoundingBox();

    if (carRect.intersectsRect(obstacleRect))
    {
        return true;
    }
    return false;
}

void SecondLevelScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if ((int)keyCode == 27) go_r = true;

    if ((int)keyCode == 26) go_l = true;
}

void SecondLevelScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if ((int)keyCode == 27) go_r = false;


    if ((int)keyCode == 26) go_l = false;
}

void SecondLevelScene::PauseButtonClicked(cocos2d::Ref* sender)
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

void SecondLevelScene::MusicButtonClicked(cocos2d::Ref* sender)
{
    if (playMusic)
    {
        AudioLevel2->resumeBackgroundMusic();
        musicButton->setColor(Color3B(255, 255, 255));
    }
    else
    {
        AudioLevel2->pauseBackgroundMusic();
        musicButton->setColor(Color3B(40, 41, 56));
    }
    playMusic = !playMusic;
}

void SecondLevelScene::SpawnObstacleLevel2()

{
    BoolSpawnObstacleLeftLvl2 = BoolSpawnObstacleRightLvl2 = false;
    int randomSprite = rand() % 3;  // Генерація випадкового числа від 0 до 2
    const char* spritePath;

    if (ObstacleLevel2)
    {
        ObstacleLevel2->removeFromParentAndCleanup(true);
        ObstacleLevel2 = nullptr;
    }

    switch (randomSprite)
    {
    case 0:
        spritePath = "sticks.png";
        break;
    case 1:
        spritePath = "tyres1.png";
        break;
    case 2:
        spritePath = "palky1.png";
        break;
    case 3:
        spritePath = "stone.png";
        break;

    default:
        spritePath = "sticks.png";  // За замовчуванням
        break;
    }

    int randomBool = rand() % 2;  // Генерація випадкового числа від 0 до 2
    ObstacleLevel2 = Sprite::create(spritePath);

    ObstacleLevel2->setScale(0.1f);
    this->addChild(ObstacleLevel2);

    switch (randomBool)
    {
    case 0:
        BoolSpawnObstacleRightLvl2 = true;
        ObstacleLevel2->setPosition(Vec2(330, 260));
        break;
    case 1:
        BoolSpawnObstacleLeftLvl2 = true;
        ObstacleLevel2->setPosition(Vec2(320, 260));
        break;

    default:
        BoolSpawnObstacleRightLvl2 = true;
        ObstacleLevel2->setPosition(Vec2(330, 260));
        break;
    }
}

void SecondLevelScene::SpawnBackgroundLevel2()
{

    int randomSprite = rand() % 2;  // Генерація випадкового числа від 0 до 2
    const char* spritePath;

    if (GroundLeftLevel2)
    {
        GroundLeftLevel2->removeFromParentAndCleanup(true);
        GroundLeftLevel2 = nullptr;
    }
    if (GroundRightLevel2)
    {
        GroundRightLevel2->removeFromParentAndCleanup(true);
        GroundRightLevel2 = nullptr;
    }

    switch (randomSprite)
    {
    case 0:
        spritePath = "stones.png";
        break;
    case 1:
        spritePath = "palky1.png";
        break;
    case 2:
        spritePath = "stones.png";
        break;
    default:
        spritePath = "palky1.png";  // За замовчуванням
        break;
    }

    GroundRightLevel2 = Sprite::create(spritePath);
    GroundRightLevel2->setScale(0.1f);
    this->addChild(GroundRightLevel2);
    GroundLeftLevel2 = Sprite::create(spritePath);
    GroundLeftLevel2->setScale(0.1f);
    this->addChild(GroundLeftLevel2);

    switch (randomSprite)
    {
    case 0:
        GroundRightLevel2->setPosition(Vec2(350, 260));
        BoolSpawnGroundRightLvl2 = true;
        break;
    case 1:
        GroundRightLevel2->setPosition(Vec2(350, 260));
        BoolSpawnGroundRightLvl2 = true;
        GroundLeftLevel2->setPosition(Vec2(300, 260));
        BoolSpawnGroundLeftLvl2 = true;
        break;
    default:
        GroundLeftLevel2->setPosition(Vec2(300, 260));
        BoolSpawnGroundLeftLvl2 = true;
        break;
    }
}

