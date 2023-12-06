#pragma once

#include <cocos2d.h>
#include "GUI/CCScrollView/CCScrollView.h"
#include "ui/UIScrollView.h"
#include "ui/UIText.h"

class BattleLogLayer : public cocos2d::Layer {
public:
    static BattleLogLayer *InitLayer();
    bool Init();
    void SetSlidePosition(const cocos2d::Vec2 &pos);
    void ToggleShow();
    void AddLog(const std::string &log);

private:
    void InitConstValue();
    void InitLogContent();
    void InitMouseListener();

private:
    float layerWidth = 0.0f;
    float layerHeight = 0.0f;
    float maxOffset = 0.0f;
    float curOffset = 0.0f;
    bool isShow = false;
    float slideX = 0.0f;
    float slideY = 0.0f;
    cocos2d::ui::ScrollView *scrollView = nullptr;
    std::string battleLog;
};
