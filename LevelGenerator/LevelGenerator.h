#pragma once

#include "cocos2d.h"
#include "GameDeclare/DefineDeclare.h"
#include "GameSettleUp/GameSettleUp.h"

class LevelGenerator {
    DECLARE_SINGLETON(LevelGenerator)

public:
    void Generate();
};
