#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "ui/UIButton.h"

class MenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(bool playbackmusic);

    virtual bool init();
   // bool firstCreation = true;
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
private:
    bool playMusic = true;

    cocos2d::MenuItem* musicButton;

    void MusicButtonClicked(cocos2d::Ref* sender);

    void GoToChooseLevelScene(cocos2d::Ref* sender);

    void GoToSettings(cocos2d::Ref* sender);

    void ExitButtonClicked(cocos2d::Ref* sender);
};

#endif // __MENU_SCENE_H__