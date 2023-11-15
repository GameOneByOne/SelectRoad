#include "WelcomeScene.h"
#include <string>

#include "GameScene/ConductScene.h"
#include "GameDeclare/ImageDeclare.h"
#include "GameDeclare/PositionDeclare.h"
#include "GameDeclare/SizeDeclare.h"
#include "GameDeclare/FontDeclare.h"
#include "GameSettleUp/GameSettleUp.h"

USING_NS_CC;

namespace {
const float MENU_X_OFFSET = 30.0f;
const float MENU_Y_OFFSET = 35.0f;
}

Scene* WelcomeScene::Show()
{
    auto pRet = new (std::nothrow) WelcomeScene();
    if (pRet && pRet->Init()) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        return nullptr;
    }
}

bool WelcomeScene::Init()
{
    if (!Scene::init()) {
        return false;
    }

    InitBackground();
    InitMenu();
    return true;
}

void WelcomeScene::InitBackground()
{
    background = Sprite::create(GameDeclare::Image::welcomeBackgroundImage.path, GameDeclare::Image::welcomeBackgroundImage.rect);
    background->setAnchorPoint(GameDeclare::Position::LEFT_BOTTOM);
    
    /* 将背景图片缩放至全屏幕 */
    float scaleX = GameDeclare::Size::screen.width / background->getBoundingBox().size.width;
    float scaleY = GameDeclare::Size::screen.height / background->getBoundingBox().size.height;
    background->setScale(scaleX, scaleY);

    addChild(background, 0);
    return;
}

void WelcomeScene::InitMenu()
{
    /* 创建开始菜单包含 - 开始游戏 | 退出 */
    auto startGameLabel = Label::createWithTTF("Start Game", GameDeclare::Font::FELT_TTF, 24);
    auto startGameMenuItem = MenuItemLabel::create(startGameLabel, WelcomeScene::StartGameCallback);
    startGameMenuItem->setAnchorPoint(GameDeclare::Position::LEFT_BOTTOM);
    startGameMenuItem->setPosition(0.0f, 0.0f);
    auto quitGameLabel = Label::createWithTTF("Quit", GameDeclare::Font::FELT_TTF, 24);
    auto quitGameMenuItem = MenuItemLabel::create(quitGameLabel, WelcomeScene::QuitCallback);
    quitGameMenuItem->setAnchorPoint(GameDeclare::Position::LEFT_BOTTOM);
    quitGameMenuItem->setPosition(0.0f, -1 * MENU_Y_OFFSET);

    startMenu = Menu::create(startGameMenuItem, quitGameMenuItem, nullptr);
    float x = GameDeclare::Size::screen.width - startGameMenuItem->getBoundingBox().size.width - MENU_X_OFFSET;
    startMenu->setPosition(x, MENU_Y_OFFSET * 2);
    addChild(startMenu, 1);
    return;
}

void WelcomeScene::QuitCallback(Ref* ref)
{
    Director::getInstance()->end();
    return;
}

void WelcomeScene::StartGameCallback(Ref* ref)
{
    Director::getInstance()->replaceScene(ConductScene::Show());
    return;
}

void WelcomeScene::update(float delta)
{
    return;
}
