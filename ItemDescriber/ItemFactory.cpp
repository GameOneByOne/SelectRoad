#include "ItemFactory.h"
#include "Item.h"

std::map<std::string, std::function<Item*(void)>> ItemFactory::itemCreatorMap;

Item *ItemFactory::Create(const std::string &itemName)
{
    if (itemCreatorMap.find(itemName) == itemCreatorMap.end()) {
        return VoidItem::Create();
    }
    return itemCreatorMap[itemName]();
}

void ItemFactory::InitItemFactory()
{
    itemCreatorMap[ItemName::A_ITEM] = AItem::Create;
    itemCreatorMap[ItemName::B_ITEM] = BItem::Create;
    itemCreatorMap[ItemName::C_ITEM] = CItem::Create;
    return;
}

