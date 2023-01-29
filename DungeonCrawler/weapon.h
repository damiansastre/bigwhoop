#pragma once
#include "consumable.h"
#include "attacktype.h"
#include "weapon_sprite_offset.h"

/*
Weapon
Weapon objects are a type of consumable that allow Characters
to interact in battle.
*/
class Weapon : public Consumable
{
public:
	Weapon();
	~Weapon();
	
	//Actions
	virtual std::string GetNotification() override;
	virtual TVector2D<int> GetPlayerEquippedSprite();
	virtual std::string GetHotKey();

	//Attack
	virtual int GetAttackPower();
	virtual AttackType GetAttackType();


protected:
	int attack_power;
	std::string HotKey;
	AttackType attack_type;
};