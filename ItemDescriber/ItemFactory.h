#pragma once

#include <map>
#include <string>
#include <functional>

class Item;

class ItemFactory {
public:
    static void InitItemFactory();
    static Item *Create(const std::string &itemName);

private:
    static std::map<std::string, std::function<Item*(void)>> itemCreatorMap;
};
