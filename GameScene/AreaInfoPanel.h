#pragma once

#include <cocos2d.h>

class AreaInfoPanel : public cocos2d::Layer {
public:
    static cocos2d::Layer *InitLayer();
    bool Init();
    void update(float delta) override;
    
private:
    void InitInfoPanel();

private:
    cocos2d::Sprite *panelBackground = nullptr; // 用于显示地区信息面板的背景图
};
