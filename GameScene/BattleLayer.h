#pragma once

#include <vector>
#include <cocos2d.h>
#include "ActorModel/ActorModel.h"

class ActorNode : public cocos2d::Node {
public:
    static ActorNode *InitNode(int actorId, bool flipX = false);
    bool Init(int actorId, bool flipX);
    void update(float delta) override;

    // 这里定义一些Actor的动画调用
    void Idle() const;
    void MeleeAttack() const;
    void Hurt() const;

private:
    int id = -1;
    cocos2d::Sprite *spriteActor = nullptr;
    cocos2d::Animate *idleAnim = nullptr;
    cocos2d::Animate *hurtAnim = nullptr;
    cocos2d::Animate *meleeAttackAnim = nullptr;
};

class BattleLayer : public cocos2d::Layer {
public:
    static BattleLayer *InitLayer();
    bool Init();
    void PlaceActor();
    void PlayBattleDetails() const;
    void update(float delta) override;

private:
    std::pair<cocos2d::Vec2, cocos2d::Vec2> playersPlaceArea;
    std::pair<cocos2d::Vec2, cocos2d::Vec2> monsterPlaceArea;
    std::map<int, ActorNode *> players;
    std::map<int, ActorNode *> monsters;
};