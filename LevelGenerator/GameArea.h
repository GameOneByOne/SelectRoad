#pragma once

#include <cocos2d.h>
#include <vector>
#include "ActorModel/ActorModel.h"
#include "CardDescriber/CardDescriber.h"

enum class Area {
    LOST_FOREST
};

class GameArea {
public:
    static GameArea GetInfo(Area area);

public:
    std::string name; /* 指示当前区域的名称 */
    std::string describe; /* 指示当前区域的描述 */
    std::vector<Actor> actors; /* 指示当前区域可能遇见什么怪物 */
    std::vector<Card> cards; /* 指示当前区域可能掉落的卡牌 */
};
