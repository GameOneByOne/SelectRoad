#include "AreaInfoPanel.h"
#include "GameDeclare/PositionDeclare.h"
#include "GameDeclare/SizeDeclare.h"
#include "GameDeclare/ImageDeclare.h"

USING_NS_CC;

cocos2d::Layer *AreaInfoPanel::InitLayer()
{
    auto pRet = new (std::nothrow) AreaInfoPanel();
    if (pRet && pRet->Init()) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        return nullptr;
    }
}

bool AreaInfoPanel::Init()
{
    if (!Layer::init()) {
        return false;
    }

    InitInfoPanel();
    return true;
}

void AreaInfoPanel::InitInfoPanel()
{
    panelBackground = Sprite::create(GameDeclare::Image::infoPanelImage.path, GameDeclare::Image::infoPanelImage.rect);
    panelBackground->setAnchorPoint(GameDeclare::Position::LEFT_UP);
    float scaleX = GameDeclare::Size::screen.width / panelBackground->getBoundingBox().size.width / 4.0f;
    float scaleY =  GameDeclare::Size::screen.height / panelBackground->getBoundingBox().size.height / 4.0f;
    panelBackground->setPosition({0.0f, GameDeclare::Size::screen.height});
    panelBackground->setScale(scaleX, scaleY);
    addChild(panelBackground);
    return;
}

void AreaInfoPanel::update(float delta)
{
    return;
}
