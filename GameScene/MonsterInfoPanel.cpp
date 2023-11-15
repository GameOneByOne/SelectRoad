#include "MonsterInfoPanel.h"
#include "GameDeclare/ImageDeclare.h"
#include "GameDeclare/PositionDeclare.h"
#include "GameDeclare/SizeDeclare.h"
#include "GameSettleUp/GameSettleUp.h"

USING_NS_CC;

cocos2d::Layer *MonsterInfoPanel::InitLayer()
{
    auto pRet = new (std::nothrow) MonsterInfoPanel();
    if (pRet && pRet->Init()) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        return nullptr;
    }
}

bool MonsterInfoPanel::Init()
{
    if (!Layer::init()) {
        return false;
    }

    InitInfoPanel();
    return true;
}

void MonsterInfoPanel::InitInfoPanel()
{
    panelBackground = Sprite::create(GameDeclare::Image::infoPanelImage.path, GameDeclare::Image::infoPanelImage.rect);
    panelBackground->setAnchorPoint(GameDeclare::Position::LEFT_BOTTOM);
    float scaleX = GameDeclare::Size::screen.width / panelBackground->getBoundingBox().size.width / 3.0f;
    float scaleY =  GameDeclare::Size::screen.height / panelBackground->getBoundingBox().size.height / 3.2f;
    panelBackground->setPosition({GameDeclare::Size::screen.width * 0.66f, 0.0f});
    panelBackground->setScale(scaleX, scaleY);
    addChild(panelBackground, 1);

    const Actor &player = GameSettleUp::GetInstance().monsterActors[0];
    HPLabel = Label::createWithSystemFont(StringUtils::format("HP = %d", player.HP), "Arial", 16);
    attackLabel = Label::createWithSystemFont(StringUtils::format("Attack = %d", player.attack), "Arial", 16);
    defenseLabel = Label::createWithSystemFont(StringUtils::format("Defense = %d", player.defense), "Arial", 16);

    HPLabel->setAnchorPoint(GameDeclare::Position::LEFT_BOTTOM);
    attackLabel->setAnchorPoint(GameDeclare::Position::LEFT_BOTTOM);
    defenseLabel->setAnchorPoint(GameDeclare::Position::LEFT_BOTTOM);

    HPLabel->setTextColor(Color4B::BLACK);
    attackLabel->setTextColor(Color4B::BLACK);
    defenseLabel->setTextColor(Color4B::BLACK);

    Rect postRect = panelBackground->getBoundingBox();
    HPLabel->setPosition({postRect.origin.x + 10.0f, postRect.origin.y + postRect.size.height / 4.0f * 1.0f});
    attackLabel->setPosition({postRect.origin.x + 10.0f, postRect.origin.y + postRect.size.height / 12.0f * 5.0f});
    defenseLabel->setPosition({postRect.origin.x + 10.0f, postRect.origin.y + postRect.size.height / 4.0f * 3.0f});
    addChild(HPLabel, 2);
    addChild(attackLabel, 2);
    addChild(defenseLabel, 2);
    return;
}

void MonsterInfoPanel::update(float delta)
{
    const Actor &player = GameSettleUp::GetInstance().monsterActors[0];
    HPLabel->setString(StringUtils::format("HP = %d", player.HP));
    attackLabel->setString(StringUtils::format("Attack = %d", player.attack));
    defenseLabel->setString(StringUtils::format("Defense = %d", player.defense));
    return;
}

