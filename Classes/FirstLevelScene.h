
#ifndef __FIRSTLEVEL_SCENE_H__
#define __FIRSTLEVEL_SCENE_H__

#include "cocos2d.h"

class FirstLevelScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    
    int score = 0;
    int lives = 3;
    CREATE_FUNC(FirstLevelScene);
private:
    cocos2d::Sprite* CarLevel1;
    cocos2d::Sprite* LivesIndicator;
    cocos2d::Sprite* ObstacleLevel1;
    cocos2d::Sprite* GroundLeft;
    cocos2d::Sprite* GroundRight;

    void update(float dt);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void PauseButtonClicked(cocos2d::Ref* sender);
    void MusicButtonClicked(cocos2d::Ref* sender);
    bool go_r = false;
    bool go_l = false;
    bool pause = false;
    bool playMusic = true;
    void SpawnObstacle();
    bool checkCollision();
    
    float elapsedTime;
    bool BoolSpawnObstacleLeft = false;
    bool BoolSpawnObstacleRight = false;
    bool BoolSpawnGroundLeft = false;
    bool BoolSpawnGroundRight = false;
    

    cocos2d::MenuItem* musicButton;
    cocos2d::MenuItem* pauseButton;
    cocos2d::Label* lifesLabel;
    cocos2d::Label* scoreLabel;
    cocos2d::Label* PauseLabel;
  
};

#endif // __HELLOWORLD_SCENE_H__
