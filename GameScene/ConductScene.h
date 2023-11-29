#pragma once

#include "cocos2d.h"
#include "ActorInfoSlideLayer.h"
#include "BattleLayer.h"

class ConductScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* Show();
    bool InitScene();
    virtual void update(float delta) override;

private:
    void InitBeforeBattleMenu();
    static void CheckPartnerInfoCallback(Ref* ref);
    static void OpenBattleLogCallback(Ref *ref);
    static void NextLevelCallback(Ref *ref);

    void InitBattlingMenu();
    static void AccelerateBattleCallback(Ref *ref);

private:
    BattleLayer *battleLayer = nullptr;
    ActorInfoSlideLayer *actorInfoSlideLayer = nullptr;
    
    // 用户菜单组
    cocos2d::Menu *beforeBattleMenus = nullptr;
    cocos2d::Menu *battlingMenus = nullptr;
};
