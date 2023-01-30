#pragma once
#include "enemy.h"

enum class BossType : uint8_t
{
	OGRE,
	WATERALIEN,
	FIRELORD,
	ELECTRICHICHEN,
	MAGICSPACEMAN,
	BOSS_NUM, // Easy way of getting the amount of enemies for random creation when creating a room
};

/*
Boss
Boss enemies contain specific resistances for combat.
*/

class Boss : public Enemy
{
public:
	Boss() {};
	~Boss() {};

	virtual void SetResistance(AttackType resistance);
	virtual AttackType GetResistance();
	virtual ActionResponse Attack(Player* player) override;
protected:
	AttackType resistance;
};

