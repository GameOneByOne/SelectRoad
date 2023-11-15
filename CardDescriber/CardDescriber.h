#pragma once

#include <string>
#include <functional>

enum class CardLevel {
    ONE,
    TWO,
    THREE
};

enum class CardType {
    ADDITION,
    ACTIVE_SKILL,
    POSITIVE_SKILL
};

enum class CardDescriber {
    HPAddCard,
    AttackAddCard,
    DefenseAddCard
};

class Card { // 是卡牌描述器的具体实例，在游戏过程中都会控制Card这个类来使用
public:
    static Card Get(CardDescriber cardDescriber);

public:
    // 卡牌基本信息
    std::string name; // 卡牌名称
    CardLevel level; // 卡牌的等级
    CardType type; // 卡牌的类型，分为加成性，主动技能性和被动技能性
    std::string describe; // 卡牌的描述
    std::string imagePath; // 卡牌的资源路径

    // 卡牌属性加成信息
    int HPAddition = 0; // 生命值加成
    int attackAddition = 0; // 攻击力加成
    int defenseAddition = 0; // 防御力加成
    int luckAddition = 0; // 幸运值加成
    int duckAddition = 0; // 闪避值加成
    int coolnessAddition = 0; // 冷静值加成

    // 卡牌特殊机制
    std::function<void(void)> activeSkill = nullptr; // 主动技能，依概率释放
    std::function<void(void)> passiveSkill = nullptr; // 被动技能, 每回合会自动检测
};
