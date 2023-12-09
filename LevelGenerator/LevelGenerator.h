#pragma once

#include "GameDeclare/DefineDeclare.h"
#include "GameSettleUp/GameSettleUp.h"

class LevelGenerator {
    DECLARE_SINGLETON(LevelGenerator)

public:
    static void Generate(const AreaName &areaName);
};
