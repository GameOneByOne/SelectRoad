#pragma once

#include <cocos2d.h>
#include <vector>
#include "ActorModel/ActorModel.h"
#include "ItemDescriber/Item.h"

enum class AreaName {
    LOST_FOREST
};

class GameArea {
public:
    static GameArea GetInfo(AreaName area);
    std::vector<std::string> GetDropItems();

public:
    int monsterMaxNum = 0; /* 指示当前区域最大可能有多少个怪物 */
    
    std::string name; /* 指示当前区域的名称 */
    std::string describe; /* 指示当前区域的描述 */
    std::string areaMapFilePath; /* 指示当前区域的背景图案 */
    std::vector<ActorName> monsters; /* 指示当前区域可能遇见什么怪物 */
    std::vector<std::string> dropItems; /* 指示当前区域可能掉落的物品 */
};
