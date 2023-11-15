#pragma once

#include <cocos2d.h>
#include <vector>
#include <CardDescriber/CardDescriber.h>

enum class ActorModel {
    PLAYER,
    MONSTER_ONE,
    MONSTER_TWO
};

class Actor {
public:
    static Actor Create(ActorModel model);

    void AddCard(Card card);

public:
    // 基础属性
    int HP; // 生命值
    int HPMax; // 最大生命值
    int attack; // 攻击力
    int defense; // 防御力

    // Buff属性
    int luck; // 幸运值
    int duck; // 闪避值
    int coolness; // 冷静值

    // 动画相关
    cocos2d::Animate *idleAnim = nullptr;
    cocos2d::Animate *attackAnim = nullptr;
    cocos2d::Animate *hurtAnim = nullptr;

private:
    void AddAdditionCard(Card card);
};
