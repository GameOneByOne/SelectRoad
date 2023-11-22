#pragma once

#include <string>
#include <cocos2d.h>
#include "GameDeclare/AnimDeclare.h"

namespace GameUtils {
/* 字符相关 */
std::string FormatIndex(int index, int length = 3);

/* 数字相关 */
int GetRandomFromRange(const std::pair<int, int> &range);

/* 动画相关 */
cocos2d::Animate *GetAnimate(GameDeclare::Anim::AnimInfo animInfo, float delay = 0.05f, unsigned int loops = -1);
}
