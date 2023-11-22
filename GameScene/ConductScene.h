#pragma once

#include "cocos2d.h"
#include "SingleActorInfoPanel.h"
#include "GameScene/BattlePanel.h"

class ConductScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* Show();
    bool InitScene();
    virtual void update(float delta) override;

private:
    cocos2d::Layer *battlePanel = nullptr;
    cocos2d::Layer *actorInfoPanel = nullptr;
};
