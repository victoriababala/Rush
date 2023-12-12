
#ifndef __SECONDLEVEL_SCENE_H__
#define __SECONDLEVEL_SCENE_H__

#include "cocos2d.h"

class SecondLevelScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    int score = 0;
    int lives = 3;
    
private:
    cocos2d::Sprite* CarLevel2;
    cocos2d::Sprite* LivesIndicator;
    cocos2d::Sprite* ObstacleLevel2;
    cocos2d::Sprite* GroundLeftLevel2;
    cocos2d::Sprite* GroundRightLevel2;
    cocos2d::Sprite* Skorpio;

    void update(float dt);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void PauseButtonClicked(cocos2d::Ref* sender);
    void MusicButtonClicked(cocos2d::Ref* sender);
    bool go_r = false;
    bool go_l = false;
    bool pause = false;
    bool playMusic = true;
    void SpawnObstacleLevel2();
    void SpawnBackgroundLevel2();
    bool checkCollision();

    float elapsedTime;
    bool BoolSpawnObstacleLeftLvl2 = false;
    bool BoolSpawnObstacleRightLvl2 = false;
    bool BoolSpawnGroundLeftLvl2 = false;
    bool BoolSpawnGroundRightLvl2 = false;

    cocos2d::MenuItem* musicButton;
    cocos2d::MenuItem* pauseButton;
    cocos2d::Label* lifesLabel;
    cocos2d::Label* scoreLabel;
    cocos2d::Label* PauseLabel;

    CREATE_FUNC(SecondLevelScene);
};

#endif // __HELLOWORLD_SCENE_H__
