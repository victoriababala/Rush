
#include "ThirdLevelScene.h"
#include "SimpleAudioEngine.h"
#include <GameOverScene.h>
#define TRANSITION_TIME 0.8
USING_NS_CC;

Scene* ThirdLevelScene::createScene()
{
    return ThirdLevelScene::create();
}

auto AudioLevel3 = CocosDenshion::SimpleAudioEngine::getInstance();
bool ThirdLevelScene::init()
{
   
    if ( !Scene::init() )
    {
        return false;
    }

    schedule(CC_SCHEDULE_SELECTOR(ThirdLevelScene::update));

    auto listener = EventListenerKeyboard::create();

    listener->onKeyPressed = CC_CALLBACK_2(ThirdLevelScene::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(ThirdLevelScene::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto BackgroundLevel3 = Sprite::create("backlevel3.1.jpg");
    BackgroundLevel3->setAnchorPoint(Vec2(0.5, 0.5));
    BackgroundLevel3->setScale(1.5);
    BackgroundLevel3->setPosition(Vec2(visibleSize.width / 2 - 50, visibleSize.height / 2));
    this->addChild(BackgroundLevel3, 0);
    auto AnimationLevel3 = Animation::create();
    AnimationLevel3->addSpriteFrameWithFile("backlevel3.1.jpg");
    AnimationLevel3->addSpriteFrameWithFile("backlevel3.2.jpg");
    AnimationLevel3->setDelayPerUnit(0.3f);
    Animate* animate = Animate::create(AnimationLevel3);
    BackgroundLevel3->runAction(RepeatForever::create(animate));


    LivesIndicator = Sprite::create("3_livespicture.png");
    LivesIndicator->setPosition(Vec2(220, 850));
    LivesIndicator->setScale(0.7);
    this->addChild(LivesIndicator);

    PauseLabel = Label::createWithTTF("PAUSED", "fonts/ARCADECLASSIC.ttf", 120);
    PauseLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    PauseLabel->setColor(Color3B::BLACK);
    PauseLabel->setVisible(false);
    this->addChild(PauseLabel);

    CarLevel3 = Sprite::create("level3car.png");
    CarLevel3->setPosition(Vec2(visibleSize.width / 2 + origin.x, 70));
    CarLevel3->setScale(0.7);
    this->addChild(CarLevel3);

    Plane = Sprite::create("plane3.png");
    Plane->setPosition(Vec2(500, 460));
    Plane->setScale(0.3);
    this->addChild(Plane);

    ObstacleLevel3 = nullptr;


    lifesLabel = Label::createWithTTF("Lives  " + std::to_string(lives), "fonts/ARCADECLASSIC.ttf", 45);
    lifesLabel->setPosition(Vec2(100, 850));
    lifesLabel->setColor(Color3B::WHITE);
    this->addChild(lifesLabel);

    scoreLabel = Label::createWithTTF("Score  " + std::to_string(score), "fonts/ARCADECLASSIC.ttf", 50);
    scoreLabel->setPosition(Vec2(650, 850));
    scoreLabel->setColor(Color3B::WHITE);
    this->addChild(scoreLabel);


    pauseButton = MenuItemImage::create("pause_button.png", "pause_button.png", CC_CALLBACK_1(ThirdLevelScene::PauseButtonClicked, this));
    pauseButton->setPosition(Point(350, 850));
    pauseButton->setScale(1.3);


    musicButton = MenuItemImage::create("musiconbutton.png", "musiconbutton.png", CC_CALLBACK_1(ThirdLevelScene::MusicButtonClicked, this));
    musicButton->setPosition(Point(470, 855));
    musicButton->setScale(0.5);

    auto menu = Menu::create(pauseButton, musicButton, NULL);
    menu->setPosition(Point::ZERO);

    this->addChild(menu);

    elapsedTime = 0;
    SpawnBackgroundLevel3();
   
    return true;
}

void ThirdLevelScene::update(float dt)
{
    Point p = CarLevel3->getPosition();

    if (p.x < 630) {
        if (go_r) CarLevel3->setPosition(Vec2(p.x + 5, p.y));
    }
    if (p.x > 120) {
        if (go_l) CarLevel3->setPosition(Vec2(p.x - 5, p.y));
    }
    elapsedTime += dt;

    if (elapsedTime >= 1.7f)
    {
        elapsedTime = 0;
        SpawnObstacleLevel3();
        SpawnBackgroundLevel3();
    }


    if ((ObstacleLevel3))
    {
        float progress = elapsedTime / 1.7f;
        float scale = 0.1f + progress * (0.8f - 0.1f);

        float progress1 = elapsedTime / 2.0f;
        Vec2 position1 = Vec2(400 - progress1 * 1400, 460 + progress1 * 300);
        Plane->setPosition(position1);

        if (BoolSpawnObstacleLeftLvl3)
        {
            Vec2 position = Vec2(370 - progress * 100, 300 - progress * 300);
            ObstacleLevel3->setScale(scale);
            ObstacleLevel3->setPosition(position);

        }
        else if (BoolSpawnObstacleRightLvl3)
        {
            Vec2 position = Vec2(370 + progress * 200, 300 - progress * 300);
            ObstacleLevel3->setScale(scale);
            ObstacleLevel3->setPosition(position);

        }

        if (checkCollisionLevel3())
        {

            AudioLevel3->preloadEffect("hitsound.wav");
            AudioLevel3->playEffect("hitsound.wav");
            lives--;
            lifesLabel->setString("Lives  " + std::to_string(lives));

            if (lives == 0)
            {
                auto scene = GameOverScene::createScene(score);
                AudioLevel3->stopBackgroundMusic();

                AudioLevel3->preloadEffect("gameover.mp3");
                AudioLevel3->playEffect("gameover.mp3");
                LivesIndicator->setTexture("0_livespicture.png");
                /*Sleep(1500);*/
                Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
            }
            else if (lives == 2) LivesIndicator->setTexture("2_livespicture.png");
            else if (lives == 1) LivesIndicator->setTexture("1_livepicture.png");
            ObstacleLevel3->removeFromParent();
            ObstacleLevel3 = nullptr;
        }
        else
        {
            score += 1;
            scoreLabel->setString("Score  " + std::to_string(score));
        }

        if (GroundLeftLevel3 && BoolSpawnGroundLeftLvl3)
        {
            float progress = elapsedTime / 1.7f;
            float scale = 0.2f + progress * (0.5f - 0.1f);


            Vec2 position = Vec2(360 - progress * 300, 320 - progress * 90);
            GroundLeftLevel3->setScale(scale);
            GroundLeftLevel3->setPosition(position);



        }
        if (GroundRightLevel3 && BoolSpawnGroundRightLvl3)
        {
            float progress = elapsedTime / 1.7f;
            float scale = 0.2f + progress * (0.5f - 0.1f);


            Vec2 position = Vec2(380 + progress * 320, 320 - progress * 90);
            GroundRightLevel3->setScale(scale);
            GroundRightLevel3->setPosition(position);

        }

    }

}
bool ThirdLevelScene::checkCollisionLevel3()
{
    Rect carRect = CarLevel3->getBoundingBox();
    Rect obstacleRect = ObstacleLevel3->getBoundingBox();

    if (carRect.intersectsRect(obstacleRect))
    {
        return true;
    }
    return false;
}

void ThirdLevelScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if ((int)keyCode == 27) go_r = true;

    if ((int)keyCode == 26) go_l = true;
}

void ThirdLevelScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if ((int)keyCode == 27) go_r = false;


    if ((int)keyCode == 26) go_l = false;
}

void ThirdLevelScene::PauseButtonClicked(cocos2d::Ref* sender)
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

void ThirdLevelScene::MusicButtonClicked(cocos2d::Ref* sender)
{
    if (playMusic)
    {
        AudioLevel3->resumeBackgroundMusic();
        musicButton->setColor(Color3B(255, 255, 255));
    }
    else
    {
        AudioLevel3->pauseBackgroundMusic();
        musicButton->setColor(Color3B(40, 41, 56));
    }
    playMusic = !playMusic;
}

void ThirdLevelScene::SpawnObstacleLevel3()

{
    BoolSpawnObstacleLeftLvl3 = BoolSpawnObstacleRightLvl3 = false;
    int randomSprite = rand() % 3;  // Генерація випадкового числа від 0 до 2
    const char* spritePath;

    if (ObstacleLevel3)
    {
        ObstacleLevel3->removeFromParentAndCleanup(true);
        ObstacleLevel3 = nullptr;
    }

    switch (randomSprite)
    {
    case 0:
        spritePath = "trashheap.png";
        break;
    case 1:
        spritePath = "tyres2.png";
        break;
    case 2:
        spritePath = "palky1.png";
        break;
    case 3:
        spritePath = "trashheap.png";
        break;

    default:
        spritePath = "palky1.png";  // За замовчуванням
        break;
    }

    int randomBool = rand() % 3;  // Генерація випадкового числа від 0 до 2
    ObstacleLevel3 = Sprite::create(spritePath);

    ObstacleLevel3->setScale(0.1f);
    this->addChild(ObstacleLevel3);

    switch (randomBool)
    {
    case 0:
        BoolSpawnObstacleRightLvl3 = true;
        ObstacleLevel3->setPosition(Vec2(330, 300));
        break;
    case 1:
        BoolSpawnObstacleLeftLvl3 = true;
        ObstacleLevel3->setPosition(Vec2(320, 300));
        break;

    default:
        BoolSpawnObstacleRightLvl3 = true;
        ObstacleLevel3->setPosition(Vec2(330, 300));
        break;
    }
}

void ThirdLevelScene::SpawnBackgroundLevel3()
{

    int randomSprite = rand() % 3;  // Генерація випадкового числа від 0 до 2
    const char* spritePath;

    if (GroundLeftLevel3)
    {
        GroundLeftLevel3->removeFromParentAndCleanup(true);
        GroundLeftLevel3 = nullptr;
    }
    if (GroundRightLevel3)
    {
        GroundRightLevel3->removeFromParentAndCleanup(true);
        GroundRightLevel3 = nullptr;
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
        spritePath = "stone3.png";
        break;
    default:
        spritePath = "palky1.png";  // За замовчуванням
        break;
    }

    GroundRightLevel3 = Sprite::create(spritePath);
    GroundRightLevel3->setScale(0.1f);
    this->addChild(GroundRightLevel3);
    GroundLeftLevel3 = Sprite::create(spritePath);
    GroundLeftLevel3->setScale(0.1f);
    this->addChild(GroundLeftLevel3);

    switch (randomSprite)
    {
    case 0:
        GroundRightLevel3->setPosition(Vec2(380, 300));
        BoolSpawnGroundRightLvl3 = true;
        break;
    case 1:
        GroundRightLevel3->setPosition(Vec2(380, 300));
        BoolSpawnGroundRightLvl3 = true;
        GroundLeftLevel3->setPosition(Vec2(360, 300));
        BoolSpawnGroundLeftLvl3 = true;
        break;
    default:
        GroundLeftLevel3->setPosition(Vec2(360, 300));
        BoolSpawnGroundLeftLvl3 = true;
        break;
    }
}




