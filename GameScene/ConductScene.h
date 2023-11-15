#pragma once

#include "cocos2d.h"
#include "GameScene/ActorInfoPanel.h"
#include "GameScene/MonsterInfoPanel.h"
#include "GameScene/AreaInfoPanel.h"
#include "GameScene/SelectPanel.h"
#include "GameScene/BattlePanel.h"

class ConductScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* Show();
    bool Init();
    virtual void update(float delta);

private:
    void InitConductLogPanel();

private:
    cocos2d::Layer *battlePanel = nullptr;
    cocos2d::Layer *actorInfoPanel = nullptr;
    cocos2d::Sprite *conductLogPanel = nullptr;
    cocos2d::Layer *monsterInfoPanel = nullptr;
    cocos2d::Layer *areaInfoPanel = nullptr;
    cocos2d::Layer *selectInfoPanel = nullptr;
};
