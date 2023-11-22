#pragma once

#include <vector>
#include <cocos2d.h>
#include "ActorModel/ActorModel.h"

class BattlePanel : public cocos2d::Layer {
public:
    static cocos2d::Layer *InitLayer();
    bool Init();
    void update(float delta) override;

private:
    void InitPlayer();
    void InitMonster();

private:
    cocos2d::Sprite *player = nullptr;
    cocos2d::Sprite *monster = nullptr;

    std::vector<Actor> playersInfo; // 存储下次应该更新的玩家数据
    std::vector<Actor> monstersInfo; // 存储下次应该更新的怪物数据

    bool playerOtherAniRunning = false; // 判定玩家是否有除了Idle以外其他动画在播放
    bool monsterOtherAniRunning = false; // 判定怪物是否有除了Idle以外其他动画在播放
};