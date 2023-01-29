#include "sword.h"
Sword::Sword()
{
	sprite_offset = {SWORD_X, SWORD_Y};
	attack_power = 20;
	attack_type = AttackType::PHYSICAL;
	name = "Mighty Sword";
	HotKey = "S";
}
Sword::Sword(std::string name, TVector2D<int> position)
{
	this->position = position;
	Sword();
}
Sword::~Sword()
{

}
TVector2D<int> Sword::GetPlayerEquippedSprite()
{
	return { SWORD_EQUIPPED_X, SWORD_EQUIPPED_Y };
}