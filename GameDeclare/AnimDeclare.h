#pragma once
#include <cocos2d.h>
#include <string>

enum ANIM_TAG {
    IDLE = 0,
    HURT = 1,
    MELEE_ATTACK = 2
};

namespace GameDeclare {
namespace Anim {
const std::string animDir = "anim/Actor/";

struct AnimInfo {
    std::string prefixPath;
    int animNum;
    std::string suffixPath;
    cocos2d::Rect rect = {0.0f, 0.0f, 900.0f, 900.0f};
};

/* 玩家的动画 */
const AnimInfo playerIdleAnim = {animDir + "FallenAngels/Idle/0_Fallen_Angels_Idle_", 18, ".png"};
const AnimInfo playerAttackAnim = {animDir + "FallenAngels/Slashing/0_Fallen_Angels_Slashing_", 12, ".png"};
const AnimInfo playerHurtAnim = {animDir + "FallenAngels/Hurt/0_Fallen_Angels_Hurt_", 12, ".png"};

/* 格伦石人的动画 */
const AnimInfo golemIdleAnim = {animDir + "GolemOne/Idle/0_Golem_Idle_", 18, ".png"};
const AnimInfo golemAttackAnim = {animDir + "GolemOne/Slashing/0_Golem_Slashing_", 12, ".png"};
const AnimInfo golemHurtAnim = {animDir + "GolemOne/Hurt/0_Golem_Hurt_", 12, ".png"};

}
}

