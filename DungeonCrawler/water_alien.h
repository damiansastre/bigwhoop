
#pragma once
#include "boss.h"

class WaterAlien : public Boss
{
public:
	WaterAlien() {
		sprite_offset = { WATER_ALIEN_BOSS_OFFSET_X,
						  WATER_ALIEN_BOSS_OFFSET_Y };
		dead_sprite_offset = { WATER_ALIEN_BOSS_OFFSET_DEAD_X ,
							   WATER_ALIEN_BOSS_OFFSET_DEAD_Y };
		attack_power = 90;
		health = 30;
		name = "Water ALien";
		resistance = AttackType::WATER;
	};
	~WaterAlien() {};
};

