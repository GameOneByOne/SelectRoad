#pragma once
#include <cocos2d.h>
#include <string>

namespace GameDeclare {
namespace Image {
const std::string imageDir = "image/";
struct ImageInfo {
std::string path;
cocos2d::Rect rect;
};

/* 背景图声明 */
const ImageInfo welcomeBackgroundImage = {imageDir + "WelcomeBg.png", {0.0f, 0.0f, 1920.0f, 1080.0f}};

/* 一些通用的现代风Panel */
const ImageInfo infoPanelImage = {imageDir + "ActorInfoPanel.png", {0.0f, 180.0f, 774.0f, 350.0f}};
const ImageInfo infoPanelTwoImage = {imageDir + "SelectPanel.png"};

/* 红色进度条图片组 */
const ImageInfo HPLeftCircleImage = {imageDir + "HP/meter_icon_holder_red.png"};
const ImageInfo HPCenterImage = {imageDir + "HP/meter_bar_holder_center-repeating_red.png"};
const ImageInfo HPRightEdgeImage = {imageDir + "HP/meter_bar_holder_right_edge_red.png"};
const ImageInfo HPValueCenterImage = {imageDir + "HP/meter_bar_center-repeating_red.png"};
const ImageInfo HPValueRightEdgeImage = {imageDir + "HP/meter_bar_right_edge_red.png"};

/* 角色属性的图标 */
const ImageInfo blueCircleImage =  {imageDir + "Icon/blue_circle.png"};
const ImageInfo blownCircleImage =  {imageDir + "Icon/blown_circle.png"};
const ImageInfo yellowCircleImage =  {imageDir + "Icon/yellow_circle.png"};
const ImageInfo pinkCircleImage =  {imageDir + "Icon/pink_circle.png"};
const ImageInfo purpleCircleImage =  {imageDir + "Icon/purple_circle.png"};

const ImageInfo attackIconImage = {imageDir + "Icon/attack.png"};
const ImageInfo defenseIconImage = {imageDir + "Icon/defense.png"};
const ImageInfo duckIconImage = {imageDir + "Icon/duck.png"};
const ImageInfo luckIconImage = {imageDir + "Icon/luck.png"};
const ImageInfo coolnessIconImage = {imageDir + "Icon/coolness.png"};

/* 卡牌图标 */
const ImageInfo HPAdditionImage = {imageDir + "Card/HP_addition.png"};
const ImageInfo defenseAdditionImage = {imageDir + "Card/defense_addition.png"};
const ImageInfo attackAdditionImage = {imageDir + "Card/attack_addition.png"};
}
}


