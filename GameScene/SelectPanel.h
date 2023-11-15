#pragma once

#include <cocos2d.h>
#include "CardDescriber/CardDescriber.h"

class SelectPanel : public cocos2d::Layer {
public:
    static cocos2d::Layer *InitLayer();
    bool Init();
    
private:
    void InitPanel();
    void InitSelectInfo();
    void InitSelectListener();
    void OnMouseUp(cocos2d::EventMouse* event);

private:
    cocos2d::Sprite *selectPanel = nullptr;
    std::vector<cocos2d::Node *> cardSelects;
};
