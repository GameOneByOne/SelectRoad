#pragma once

#include <cocos2d.h>

#include "GUI/CCScrollView/CCScrollView.h"
#include "ui/UIScrollView.h"

class ActorInfoSlideLayer : public cocos2d::Layer {
public:
    static ActorInfoSlideLayer *InitLayer();
    bool Init();
    void update(float delta);
    void SetSlidePosition(const cocos2d::Vec2 &pos);
    void ToggleShow();

private:
    void InitConstValue();
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
};
