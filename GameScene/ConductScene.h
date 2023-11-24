#pragma once

#include "cocos2d.h"
#include "SingleActorInfoPanel.h"
#include "BattleLayer.h"

class ConductScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* Show();
    bool InitScene();
    virtual void update(float delta) override;

private:
    BattleLayer *battleLayer = nullptr;
    cocos2d::Layer *actorInfoPanel = nullptr;
};
