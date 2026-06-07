#pragma once

enum class ItemBaseTypeVangeloovenMichal
{
	Food,
	Medkit,
	Weapon,
	Null
};


static constexpr std::array<ItemBaseTypeVangeloovenMichal, 5> g_IdealInventory{
	ItemBaseTypeVangeloovenMichal::Food, ItemBaseTypeVangeloovenMichal::Medkit, ItemBaseTypeVangeloovenMichal::Weapon,
	ItemBaseTypeVangeloovenMichal::Weapon, ItemBaseTypeVangeloovenMichal::Weapon
};


inline ItemBaseTypeVangeloovenMichal ItemToBaseItemType(EItemType Item)
{
	switch (Item)
	{
	case EItemType::Food:
		return ItemBaseTypeVangeloovenMichal::Food;
	case EItemType::Medkit:
		return ItemBaseTypeVangeloovenMichal::Medkit;
	case EItemType::Shotgun:
	case EItemType::Pistol:
		return ItemBaseTypeVangeloovenMichal::Weapon;
	case EItemType::Garbage:
	default:
		return ItemBaseTypeVangeloovenMichal::Null;
	}
}
