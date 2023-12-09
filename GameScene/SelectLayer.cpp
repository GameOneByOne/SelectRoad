#include "SelectLayer.h"

#include "GameDeclare/FontDeclare.h"
#include "GameDeclare/PositionDeclare.h"
#include "GameDeclare/SizeDeclare.h"
#include "GameSettleUp/GameSettleUp.h"
#include "ItemDescriber/ItemFactory.h"

USING_NS_CC;

SelectLayer *SelectLayer::InitLayer()
{
    auto pRet = new (std::nothrow) SelectLayer();
    if (pRet && pRet->Init()) {
        return pRet;
    } else {
        delete pRet;
        return nullptr;
    }
}

bool SelectLayer::Init()
{
    if (!Layer::init()) {
        return false;
    }

    itemPanelWidth = GameDeclare::Size::screen.width / 5.0f;
    itemPanelHeight = GameDeclare::Size::screen.height / 4.0f;
    itemPanelWidthMargin = GameDeclare::Size::screen.width / 30.0f;
    itemPanelHeightMargin = GameDeclare::Size::screen.height / 8.0f;
    return true;
}

void SelectLayer::ShowSelect()
{
    if (isSelecting) {
        return;
    }
    GameArea gameArea = GameArea::GetInfo(GameSettleUp::GetInstance().currentArea);
    /* 从关卡中获取物品掉落 */
    ShowItemSelect(gameArea.GetDropItems());
    isSelecting = true;
    return;
}

void SelectLayer::ShowItemSelect(const std::vector<std::string> &items)
{
    size_t totalItemNum = items.size();
    int row = 0;
    float x = GameDeclare::Size::screen.width / 20.0f;
    float y = GameDeclare::Size::screen.height / 8.0f * 7.0f - itemPanelHeight;
    /* 一列最多四个 */
    while (row * 4 < totalItemNum) {
        ArrangeItemsForRow(items, row, x, y);
        ++row;
        y = y - itemPanelHeight - itemPanelWidthMargin;
    }
    return;
}

void SelectLayer::ArrangeItemsForRow(const std::vector<std::string> &items, int row, float x, float y)
{
    for (size_t i = 4 * row; ((i < items.size()) && (i < 4 * (row + 1))); ++i) {
        // 先画一个方框
        DrawNode *panel = DrawNode::create();
        panel->drawRect({0.0f, 0.0f}, {itemPanelWidth, itemPanelHeight}, Color4F::BLUE);
        panel->setAnchorPoint({GameDeclare::Position::LEFT_BOTTOM});
        panel->setPosition(x, y);
        addChild(panel);

        // 展示出物品详情
        Item *item = ItemFactory::Create(items[i]);
        Label *itemName = Label::createWithTTF(item->name, GameDeclare::Font::FELT_TTF, 16);
        Label *itemDesc = Label::createWithTTF(item->describe, GameDeclare::Font::FELT_TTF, 16);
        panel->addChild(itemName);
        panel->addChild(itemDesc);
        x = x + itemPanelWidth + itemPanelWidthMargin;
    }
    return;
}

void SelectLayer::ShowActorSelect()
{
    return;
}

void SelectLayer::ShowRoadSelect()
{
    return;
}
