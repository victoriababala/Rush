

#ifndef __THIRDLEVEL_SCENE_H__
#define __THIRDLEVEL_SCENE_H__

#include "cocos2d.h"

class ThirdLevelScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    int score = 0;
    int lives = 3;

private:
    cocos2d::Sprite* CarLevel3;
    cocos2d::Sprite* Plane;
    cocos2d::Sprite* LivesIndicator;
    cocos2d::Sprite* ObstacleLevel3;
    cocos2d::Sprite* GroundLeftLevel3;
    cocos2d::Sprite* GroundRightLevel3;

    void update(float dt);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void PauseButtonClicked(cocos2d::Ref* sender);
    void MusicButtonClicked(cocos2d::Ref* sender);
    bool go_r = false;
    bool go_l = false;
    bool pause = false;
    bool playMusic = true;
    bool checkCollisionLevel3();
    void SpawnObstacleLevel3();
    void SpawnBackgroundLevel3();

    float elapsedTime;
    bool BoolSpawnObstacleLeftLvl3 = false;
    bool BoolSpawnObstacleRightLvl3 = false;
    bool BoolSpawnGroundLeftLvl3 = false;
    bool BoolSpawnGroundRightLvl3 = false;

    cocos2d::MenuItem* musicButton;
    cocos2d::MenuItem* pauseButton;
    cocos2d::Label* lifesLabel;
    cocos2d::Label* scoreLabel;
    cocos2d::Label* PauseLabel;
    
    CREATE_FUNC(ThirdLevelScene);
};

#endif // __HELLOWORLD_SCENE_H__
