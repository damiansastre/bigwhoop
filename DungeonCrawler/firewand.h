#pragma once
#include "weapon.h"

/*
FireWand
*/
class FireWand : public Weapon
{
public:
	FireWand();
	FireWand(std::string name, TVector2D<int> position);
	~FireWand();
	virtual TVector2D<int> GetPlayerEquippedSprite() override;
};