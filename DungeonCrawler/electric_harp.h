#pragma once
#include "weapon.h"
/*
ElectricHarp
*/
class ElectricHarp : public Weapon
{
public:
	ElectricHarp();
	ElectricHarp(std::string name, TVector2D<int> position);
	~ElectricHarp();
	virtual TVector2D<int> GetPlayerEquippedSprite() override;
};