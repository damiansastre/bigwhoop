#pragma once
#include "weapon.h"

/*
WaterPotion
*/
class WaterPotion : public Weapon
{
public:
	WaterPotion();
	WaterPotion(std::string name, TVector2D<int> position);
	~WaterPotion();
	virtual TVector2D<int> GetPlayerEquippedSprite() override;
};