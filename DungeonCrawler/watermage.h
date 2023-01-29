#pragma once
#include "enemy.h"
/*
WaterMage
*/
class WaterMage : public Enemy
{
public:
	WaterMage()
	{
		sprite_offset = { WATER_MAGE_OFFSET_X,
								WATER_MAGE_OFFSET_Y };
		dead_sprite_offset = { WATER_MAGE_OFFSET_DEAD_X,
									  WATER_MAGE_OFFSET_DEAD_Y };
		attack_power = 30;
		health = 30;
		name = "Water Mage";
	}
	~WaterMage();

};