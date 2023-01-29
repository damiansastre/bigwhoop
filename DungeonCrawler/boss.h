#pragma once
#include "enemy.h"

enum class BossType : uint8_t
{
	OGRE,
	//PURPLE,
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

	virtual void OnRenderedNotification() {};
};

