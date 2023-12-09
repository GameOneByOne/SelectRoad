#pragma once

#include "cocos2d.h"
#include "ActorInfoSlideLayer.h"
#include "BattleLogLayer.h"
#include "BattleLayer.h"
#include "SelectLayer.h"

class ConductScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* Show();
    bool InitScene();
    virtual void update(float delta) override;

private:
    void InitMenu();

private:
    BattleLayer *battleLayer = nullptr;
    ActorInfoSlideLayer *actorInfoSlideLayer = nullptr;
    BattleLogLayer *battleLogLayer = nullptr;
    SelectLayer *selectLayer = nullptr;    

    // 用户菜单组
    cocos2d::Menu *ConductMenus = nullptr;
};
