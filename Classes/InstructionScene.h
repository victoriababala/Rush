#ifndef __INCTRUCTION_SCENE_H__
#define __INCTRUCTION_SCENE_H__

#include "cocos2d.h"

class InstructionScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void goToMenuScene(Ref* pSender);
    

    CREATE_FUNC(InstructionScene);
};

#endif // __INCTRUCTION_SCENE_H__
