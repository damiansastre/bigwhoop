#include "waterpotion.h"
WaterPotion::WaterPotion()
{
	sprite_offset = { WATER_POTION_X, WATER_POTION_Y };
	attack_power = 20;
	attack_type = AttackType::WATER;
	name = "Water Potion";
	HotKey = "Q";
}
WaterPotion::WaterPotion(std::string name, TVector2D<int> position)
{
	this->name = name;
	this->position = position;
	WaterPotion();
}
WaterPotion::~WaterPotion()
{

}
TVector2D<int> WaterPotion::GetPlayerEquippedSprite()
{
	return { WATER_POTION_EQUIPPED_X, WATER_POTION_EQUIPPED_Y };
}