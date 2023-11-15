#include "ActorInfoPanel.h"
#include "GameDeclare/ImageDeclare.h"
#include "GameDeclare/PositionDeclare.h"
#include "GameDeclare/SizeDeclare.h"
#include "GameDeclare/FontDeclare.h"
#include "ActorModel/ActorModel.h"
#include "GameSettleUp/GameSettleUp.h"

USING_NS_CC;

cocos2d::Layer *ActorInfoPanel::InitLayer()
{
    auto pRet = new (std::nothrow) ActorInfoPanel();
    if (pRet && pRet->Init()) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        return nullptr;
    }
}

bool ActorInfoPanel::Init()
{
    if (!Layer::init()) {
        return false;
    }
    
    InitPanel();
    InitHPInfo();
    InitActorOtherInfo();
    return true;
}

void ActorInfoPanel::InitHPInfo()
{
    /* 生成Actor的HP显示形式和位置，这里其实需要好多图片拼接起来 */
    const Actor &player = GameSettleUp::GetInstance().playerActor;

    /* 先生成左侧图标框 */
    HPLeftCircle = Sprite::create(GameDeclare::Image::HPLeftCircleImage.path);
    HPLeftCircle->setAnchorPoint(GameDeclare::Position::LEFT_UP);
    HPLeftCircle->setScale(panelSize.width / HPLeftCircle->getContentSize().width / 6.0f);
    HPLeftCircle->setPosition({panelSize.width / 12.0f, panelSize.height * 5 / 6});
    addChild(HPLeftCircle, 3);
    
    /* 然后生成中间进度框 */
    Sprite *HpCenter = nullptr;
    for (int num = 0; num < 10; ++num) {
        HpCenter = Sprite::create(GameDeclare::Image::HPCenterImage.path);
        HpCenter->setScale(panelSize.width / HpCenter->getContentSize().width / 15.0f);
        HpCenter->setAnchorPoint(GameDeclare::Position::LEFT_UP);
        HpCenter->setPosition({HPLeftCircle->getPosition().x + HPLeftCircle->getBoundingBox().size.width / 2 + num * HpCenter->getBoundingBox().size.width, HPLeftCircle->getPosition().y});
        addChild(HpCenter, 1);
    }

    /* 最后生成右侧边缘框 */
    Sprite *HPRightEdge = Sprite::create(GameDeclare::Image::HPRightEdgeImage.path);
    HPRightEdge->setAnchorPoint(GameDeclare::Position::LEFT_UP);
    HPRightEdge->setScale(panelSize.width / HPRightEdge->getContentSize().width / 16.0f);
    HPRightEdge->setPosition({HPLeftCircle->getPosition().x + HPLeftCircle->getBoundingBox().size.width / 2 + 10 * HpCenter->getBoundingBox().size.width, HPLeftCircle->getPosition().y});
    addChild(HPRightEdge, 1);

    /* 然后生成玩家血量值显示部分，先生成血量值中间重复的框 */
    int curHPPercentage = player.HP * 100 / player.HPMax;
    Sprite *HpValueCenter = nullptr;
    for (int num = 0; num < curHPPercentage; ++num) {
        HpValueCenter = Sprite::create(GameDeclare::Image::HPValueCenterImage.path);
        HpValueCenter->setScale(panelSize.width / HpValueCenter->getContentSize().width / 150.0f);
        HpValueCenter->setAnchorPoint(GameDeclare::Position::LEFT_UP);
        HpValueCenter->setPosition({HPLeftCircle->getPosition().x + HPLeftCircle->getBoundingBox().size.width / 2 + num * HpValueCenter->getBoundingBox().size.width, HPLeftCircle->getPosition().y});
        addChild(HpValueCenter, 2);
        HPDynamicSprites.push_back(HpValueCenter);
    }

    /* 最后生成血量值右侧边缘框 */
    HPValueRightEdge = Sprite::create(GameDeclare::Image::HPValueRightEdgeImage.path);
    HPValueRightEdge->setAnchorPoint(GameDeclare::Position::LEFT_UP);
    HPValueRightEdge->setScale(panelSize.width / HPValueRightEdge->getContentSize().width / 16.0f);
    HPValueRightEdge->setPosition({HPLeftCircle->getPosition().x + HPLeftCircle->getBoundingBox().size.width / 2 + HPDynamicSprites.size() * HpValueCenter->getBoundingBox().size.width, HPLeftCircle->getPosition().y});
    addChild(HPValueRightEdge, 2);  
    return;
}

void ActorInfoPanel::InitActorOtherInfo()
{
    /* 生成Actor的其他信息的显示形式和位置 */
    const Actor &player = GameSettleUp::GetInstance().playerActor;
    Sprite *blueCircle = Sprite::create(GameDeclare::Image::blueCircleImage.path);
    Sprite *blownCircle = Sprite::create(GameDeclare::Image::blownCircleImage.path);
    Sprite *yellowCircle = Sprite::create(GameDeclare::Image::yellowCircleImage.path);
    Sprite *pinkCircle = Sprite::create(GameDeclare::Image::pinkCircleImage.path);
    Sprite *purpleCircle = Sprite::create(GameDeclare::Image::purpleCircleImage.path);
    Sprite *attackIcon = Sprite::create(GameDeclare::Image::attackIconImage.path);
    Sprite *defenseIcon = Sprite::create(GameDeclare::Image::defenseIconImage.path);
    Sprite *duckIcon = Sprite::create(GameDeclare::Image::duckIconImage.path);
    Sprite *luckIcon = Sprite::create(GameDeclare::Image::luckIconImage.path);
    Sprite *coolnessIcon = Sprite::create(GameDeclare::Image::coolnessIconImage.path);

    attackIcon->setAnchorPoint(GameDeclare::Position::CENTER);
    defenseIcon->setAnchorPoint(GameDeclare::Position::CENTER);
    duckIcon->setAnchorPoint(GameDeclare::Position::CENTER);
    luckIcon->setAnchorPoint(GameDeclare::Position::CENTER);
    coolnessIcon->setAnchorPoint(GameDeclare::Position::CENTER);
    blueCircle->setAnchorPoint(GameDeclare::Position::MIDDLE_BOTTOM);
    blownCircle->setAnchorPoint(GameDeclare::Position::MIDDLE_BOTTOM);
    yellowCircle->setAnchorPoint(GameDeclare::Position::MIDDLE_BOTTOM);
    pinkCircle->setAnchorPoint(GameDeclare::Position::MIDDLE_BOTTOM);
    purpleCircle->setAnchorPoint(GameDeclare::Position::MIDDLE_BOTTOM);

    /* 左边第一行第一个，攻击力显示 */
    pinkCircle->setScale(panelSize.width / pinkCircle->getContentSize().width / 12.0f);
    attackIcon->setScale(pinkCircle->getContentSize().width / attackIcon->getContentSize().width / 38.0f);
    pinkCircle->setPosition({panelSize.width / 4.0f, panelSize.height / 2.0f - pinkCircle->getBoundingBox().size.height});
    attackIcon->setPosition({pinkCircle->getPosition().x, pinkCircle->getPosition().y + pinkCircle->getBoundingBox().size.height / 2});
    attackInfoLabel = Label::createWithTTF(StringUtils::format("%d", player.attack), GameDeclare::Font::FELT_TTF, 24);
    attackInfoLabel->setAnchorPoint(GameDeclare::Position::LEFT_BOTTOM);
    attackInfoLabel->setPosition({pinkCircle->getPosition().x + pinkCircle->getBoundingBox().size.width / 2 + 5.0f, pinkCircle->getPosition().y + 5.0f});
    addChild(pinkCircle, 2);
    addChild(attackIcon, 3);
    addChild(attackInfoLabel, 2);

    /* 左边第一行第二个，防御力显示 */
    blownCircle->setScale(pinkCircle->getBoundingBox().size.width / blownCircle->getBoundingBox().size.width);
    defenseIcon->setScale(panelSize.width / defenseIcon->getContentSize().width / 30.0f);
    blownCircle->setPosition({panelSize.width / 2.0f, pinkCircle->getPosition().y});
    defenseIcon->setPosition({blownCircle->getPosition().x, attackIcon->getPosition().y});
    defenseInfoLabel = Label::createWithTTF(StringUtils::format("%d", player.defense), GameDeclare::Font::FELT_TTF, 24);
    defenseInfoLabel->setAnchorPoint(GameDeclare::Position::LEFT_BOTTOM);
    defenseInfoLabel->setPosition({blownCircle->getPosition().x + blownCircle->getBoundingBox().size.width / 2 + 5.0f, blownCircle->getPosition().y + 5.0f});
    addChild(blownCircle, 2);
    addChild(defenseIcon, 3);
    addChild(defenseInfoLabel, 2);
    
    /* 左边第二行第一个，闪避值显示 */
    blueCircle->setScale(pinkCircle->getBoundingBox().size.width / blueCircle->getBoundingBox().size.width);
    duckIcon->setScale(panelSize.width / duckIcon->getContentSize().width / 22.0f);
    blueCircle->setPosition({pinkCircle->getPosition().x, pinkCircle->getPosition().y - blueCircle->getBoundingBox().size.height - 4.0f});
    duckIcon->setPosition({blueCircle->getPosition().x, blueCircle->getPosition().y + blueCircle->getBoundingBox().size.height / 2});
    duckInfoLabel = Label::createWithTTF(StringUtils::format("%d", player.duck), GameDeclare::Font::FELT_TTF, 24);
    duckInfoLabel->setAnchorPoint(GameDeclare::Position::LEFT_BOTTOM);
    duckInfoLabel->setPosition({blueCircle->getPosition().x + blueCircle->getBoundingBox().size.width / 2 + 5.0f, blueCircle->getPosition().y + 5.0f});
    addChild(blueCircle, 2);
    addChild(duckIcon, 3);
    addChild(duckInfoLabel, 2);

    /* 左边第二行第二个，幸运值显示 */
    yellowCircle->setScale(pinkCircle->getBoundingBox().size.width / yellowCircle->getBoundingBox().size.width);
    luckIcon->setScale(panelSize.width / luckIcon->getContentSize().width / 30.0f);
    yellowCircle->setPosition({blownCircle->getPosition().x, blueCircle->getPosition().y});
    luckIcon->setPosition({yellowCircle->getPosition().x, duckIcon->getPosition().y});
    luckInfoLabel = Label::createWithTTF(StringUtils::format("%d", player.luck), GameDeclare::Font::FELT_TTF, 24);
    luckInfoLabel->setAnchorPoint(GameDeclare::Position::LEFT_BOTTOM);
    luckInfoLabel->setPosition({yellowCircle->getPosition().x + yellowCircle->getBoundingBox().size.width / 2 + 5.0f, yellowCircle->getPosition().y + 5.0f});
    addChild(yellowCircle, 2);
    addChild(luckIcon, 3);
    addChild(luckInfoLabel, 2);

    /* 左边第二行第三个， 冷静值显示 */
    purpleCircle->setScale(pinkCircle->getBoundingBox().size.width / purpleCircle->getBoundingBox().size.width);
    coolnessIcon->setScale(panelSize.width / coolnessIcon->getContentSize().width / 26.0f);
    purpleCircle->setPosition({panelSize.width / 4.0f * 3.0f, yellowCircle->getPosition().y});
    coolnessIcon->setPosition({purpleCircle->getPosition().x, duckIcon->getPosition().y});
    coolnessInfoLabel = Label::createWithTTF(StringUtils::format("%d", player.coolness), GameDeclare::Font::FELT_TTF, 24);
    coolnessInfoLabel->setAnchorPoint(GameDeclare::Position::LEFT_BOTTOM);
    coolnessInfoLabel->setPosition({purpleCircle->getPosition().x + purpleCircle->getBoundingBox().size.width / 2 + 5.0f, purpleCircle->getPosition().y + 5.0f});
    addChild(purpleCircle, 2);
    addChild(coolnessIcon, 3);
    addChild(coolnessInfoLabel, 2);
    return;
}

void ActorInfoPanel::InitPanel()
{
    /* 先确定好整个Panel的大小 */
    panelSize.width = GameDeclare::Size::screen.width / 4.0f;
    panelSize.height = GameDeclare::Size::screen.height / 4.2f;

    /* 生成整个Panel的背景和位置 */
    Sprite *panelBackground = Sprite::create(GameDeclare::Image::infoPanelImage.path, GameDeclare::Image::infoPanelImage.rect);
    panelBackground->setAnchorPoint(GameDeclare::Position::LEFT_BOTTOM);
    float scaleX = panelSize.width / panelBackground->getBoundingBox().size.width;
    float scaleY = panelSize.height / panelBackground->getBoundingBox().size.height;
    panelBackground->setScale(scaleX, scaleY);
    panelBackground->setPosition(GameDeclare::Position::LEFT_BOTTOM);
    addChild(panelBackground, 0);
    return;
}

void ActorInfoPanel::InitMouseListener()
{
    return;
}

void ActorInfoPanel::update(float delta)
{
    const Actor &player = GameSettleUp::GetInstance().playerActor;

    /* 这里动态更新玩家的血量值 */
    int curHPPercentage = player.HP * 100 / player.HPMax;
    if (curHPPercentage > HPDynamicSprites.size()) { // 如果血量需要增加
        for (int num = HPDynamicSprites.size(); num < curHPPercentage; ++num) {
            Sprite *HpValueCenter = Sprite::create(GameDeclare::Image::HPValueCenterImage.path);
            HpValueCenter->setScale(panelSize.width / HpValueCenter->getContentSize().width / 150.0f);
            HpValueCenter->setAnchorPoint(GameDeclare::Position::LEFT_UP);
            HpValueCenter->setPosition({HPLeftCircle->getPosition().x + HPLeftCircle->getBoundingBox().size.width / 2 + num * HpValueCenter->getBoundingBox().size.width, HPLeftCircle->getPosition().y});
            addChild(HpValueCenter, 2);
            HPDynamicSprites.push_back(HpValueCenter);
        }
    } else if (curHPPercentage < HPDynamicSprites.size()) { // 如果血量需要减少
        for (int num = HPDynamicSprites.size() - 1; num >= curHPPercentage; --num) {
            removeChild(HPDynamicSprites[num]);
        }
        HPDynamicSprites.erase(HPDynamicSprites.begin() + curHPPercentage, HPDynamicSprites.end());
    }
    
    if (!HPDynamicSprites.empty()) {
        HPValueRightEdge->setPositionX({panelSize.width / 6.0f + HPDynamicSprites.size() * HPDynamicSprites[0]->getBoundingBox().size.width});
    } else {
        HPValueRightEdge->setPositionX({panelSize.width / 6.0f});
    }

    /* 这里动态更新玩家的其他属性值数据 */
    attackInfoLabel->setString(StringUtils::format("%d", player.attack));
    defenseInfoLabel->setString(StringUtils::format("%d", player.defense));
    coolnessInfoLabel->setString(StringUtils::format("%d", player.coolness));
    duckInfoLabel->setString(StringUtils::format("%d", player.duck));
    luckInfoLabel->setString(StringUtils::format("%d", player.luck));
    return;
}