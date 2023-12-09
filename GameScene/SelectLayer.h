#pragma once

#include <cocos2d.h>

class SelectLayer : public cocos2d::Layer  {
public:
    static SelectLayer *InitLayer();
    bool Init();
    void ShowSelect();

private:
    void ShowItemSelect(const std::vector<std::string> &items);
    void ShowActorSelect();
    void ShowRoadSelect();

    void ArrangeItemsForRow(const std::vector<std::string> &items, int row, float x, float y);

private:
    bool isSelecting = false;
    float itemPanelWidth = 0.0f;
    float itemPanelHeight = 0.0f;
    float itemPanelWidthMargin = 0.0f;
    float itemPanelHeightMargin = 0.0f;
};
