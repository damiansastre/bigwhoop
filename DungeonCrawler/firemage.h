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
		attack_power = 20;
		health = 100;
		name = "Fire Mage";
	}
	~FireMage();
};