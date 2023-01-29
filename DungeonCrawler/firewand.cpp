#include "firewand.h"
FireWand::FireWand()
{
	sprite_offset = { FIRE_WAND_X, FIRE_WAND_Y };
	attack_power = 30;
	attack_type = AttackType::FIRE;
	name = "Fire Wand";
	HotKey = "W";
}
FireWand::FireWand(std::string name, TVector2D<int> position)
{
	this->position = position;
	FireWand();
}
FireWand::~FireWand()
{

}
TVector2D<int> FireWand::GetPlayerEquippedSprite()
{
	return { FIRE_WAND_EQUIPPED_X, FIRE_WAND_EQUIPPED_Y };
}