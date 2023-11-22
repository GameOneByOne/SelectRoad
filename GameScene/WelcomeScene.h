#pragma once

#include "cocos2d.h"

class WelcomeScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* Show();
    bool InitScene();
    virtual void update(float delta) override;

private:
    void InitMenu();
    void InitBackground();

    static void StartGameCallback(Ref* ref);
    static void QuitCallback(Ref* ref);

private:
    cocos2d::Node *background = nullptr;
    cocos2d::Menu *startMenu = nullptr;
};
