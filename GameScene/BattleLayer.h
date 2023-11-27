#pragma once

#include <vector>
#include <cocos2d.h>
#include "ActorModel/ActorModel.h"

class ActorSprite : public cocos2d::Sprite {
public:
    static ActorSprite *Create(int actorId, bool flipX = false);
    bool Init(int actorId, bool flipX);

    // 这里定义一些Actor的动画调用
    void Idle();
    bool AnimSequenceDone() const { return !runningAnim; }
    void MeleeAttackToEnemy(const cocos2d::Vec2 &position, float speed);
    void DamageFromAttacker(int damage, float delayTime);

private:
    int id = -1;
    bool runningAnim = false;
    cocos2d::Animate *idleAnim = nullptr;
    cocos2d::Animate *runAnim = nullptr;
    cocos2d::Animate *hurtAnim = nullptr;
    cocos2d::Animate *dyingAnim = nullptr;
    cocos2d::Animate *meleeAttackAnim = nullptr;
};

class BattleLayer : public cocos2d::Layer {
public:
    static BattleLayer *InitLayer();
    bool Init();
    void PlaceActor();
    void PlayBattleDetail();
    void CleanBattleLayer();
    void update(float delta) override;

private:
    ActorSprite *GetActorNodeById(int id) const;
    void PlayCommonAttackBattleDetail(const BattleDetail &detail);

private:
    std::pair<cocos2d::Vec2, cocos2d::Vec2> playersPlaceArea;
    std::pair<cocos2d::Vec2, cocos2d::Vec2> monsterPlaceArea;
    std::map<int, ActorSprite *> players;
    std::map<int, ActorSprite *> monsters;
    bool isAnimRunning = false;
};