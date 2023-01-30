#pragma once
#include "mapobject.h"	
#include "attacktype.h"

/*
Character
Characters are a type of map object that have actions
that trigger between other characters.
*/
class Character : public MapObject
{
public:
	Character();
	~Character();

	// Rendering
	virtual void SetSprite(TVector2D<int> spritePosition);

	// Movement
	virtual void Move(TVector2D<int> position);
	
	// Health Actions
	void Damage(int damage);
	void Heal(int heal);
	bool IsAlive();
	int GetHealth();

	// Attacks
	virtual int GetAttackPower();
	virtual AttackType GetAttackType();
	virtual std::string GetAttackTypeDescription(AttackType attack_type);
	virtual void Kill();

protected:
	int health = 0;
	int attack_power = 0;
	AttackType attack_type = AttackType::PHYSICAL;
	TVector2D<int> dead_sprite_offset;
};