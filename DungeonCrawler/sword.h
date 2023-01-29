#pragma once
#include "weapon.h"

/*
Sword
*/
class Sword : public Weapon
{
public:
	Sword();
	Sword(std::string name, TVector2D<int> position);
	~Sword();
	virtual TVector2D<int> GetPlayerEquippedSprite() override;
};