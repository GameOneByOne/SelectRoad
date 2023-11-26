// ReSharper disable All
#pragma once

#include <cocos2d.h>
#include "BattleCalc/BattleCalc.h"
#include "CardDescriber/CardDescriber.h"
#include "GameDeclare/AnimDeclare.h"

enum class ActorName {
    DEFAULT,
    PLAYER,
    MONSTER_ONE
};

// 这里相当于定义了一个actor的模型，其他地方会使用工厂类方法创建出来一个actor实例
class ActorModel {
public:
    // 基础属性范围
    std::pair<int, int> HPRange; // 当前生命值范围
    std::pair<int, int> attackRange; // 攻击力范围
    std::pair<int, int> defenseRange; // 防御力范围
    std::set<AttackType> canAttackTypes; // 可以进行的攻击方式

    // Buff属性范围
    std::pair<int, int> luckRange; // 幸运值范围
    std::pair<int, int> duckRange; // 闪避值范围
    std::pair<int, int> coolnessRange; // 冷静值范围

    // 动画资源
    GameDeclare::Anim::AnimInfo idleAnim;
    GameDeclare::Anim::AnimInfo runAnim;
    GameDeclare::Anim::AnimInfo hurtAnim;
    GameDeclare::Anim::AnimInfo meleeAttackAnim;
};

class Actor {
public:
    void AddCard(const Card &card); // 添加能力
    AttackType GetAttackType() const; // 随机返回一种攻击方式
    float GetDamageValue(const Actor &enemy) const; // 返回造成伤害的数值

public:
    int id; // 唯一标识，每个Actor都不一样

    // 基础属性
    int HP; // 当前生命值
    int HPMax; // 最大生命值
    int attack; // 攻击力
    int defense; // 防御力
    std::set<AttackType> canAttackTypes; // 可以进行的攻击方式

    // Buff属性
    int luck; // 幸运值
    int duck; // 闪避值
    int coolness; // 冷静值

    // 动画相关
    GameDeclare::Anim::AnimInfo idleAnim;
    GameDeclare::Anim::AnimInfo runAnim;
    GameDeclare::Anim::AnimInfo hurtAnim;
    GameDeclare::Anim::AnimInfo meleeAttackAnim;

    // 用于其他用途的数据
    bool canAttack = true;

private:
    void AddAdditionCard(const Card &card);
};
