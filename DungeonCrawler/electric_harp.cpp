#include "electric_harp.h"
ElectricHarp::ElectricHarp()
{
	sprite_offset = { ELECTRIC_HARP_X, ELECTRIC_HARP_Y };
	attack_power = 20;
	attack_type = AttackType::ELECTRIC;
	name = "Electric Harp";
	HotKey = "E";
}
ElectricHarp::ElectricHarp(std::string name, TVector2D<int> position)
{
	this->name = name;
	this->position = position;
	ElectricHarp();
}
ElectricHarp::~ElectricHarp()
{

}
TVector2D<int> ElectricHarp::GetPlayerEquippedSprite()
{
	return { ELECTRIC_HARP_EQUIPPED_X, ELECTRIC_HARP_EQUIPPED_Y };
}