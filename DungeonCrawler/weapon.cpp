#include "weapon.h"
#include "player.h"
Weapon::Weapon()
{

}

Weapon::~Weapon()
{
}

TVector2D<int> Weapon::GetPlayerEquippedSprite()
{
	return TVector2D<int>(0, 0);
}

int Weapon::GetAttackPower()
{
	return attack_power;
}
AttackType Weapon::GetAttackType()
{
	return attack_type;
}
std::string Weapon::GetHotKey()
{
	return HotKey;
}

std::string Weapon::GetNotification()
{
	return "You got " + name;
}