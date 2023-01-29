#pragma once
#include "enemy.h"

/*
FireMage
*/
class FireMage : public Enemy
{
public:
	FireMage() {
		sprite_offset = { FIRE_MAGE_OFFSET_X, FIRE_MAGE_OFFSET_Y };
		dead_sprite_offset = { FIRE_MAGE_OFFSET_DEAD_X, FIRE_MAGE_OFFSET_DEAD_Y };
		attack_power = 1000;
		health = 1000;
		name = "Fire Mage";
	}
	~FireMage();
};