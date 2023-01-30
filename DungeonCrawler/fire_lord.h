#pragma once
#pragma once
#include "boss.h"

class FireLord : public Boss
{
public:
	FireLord() {
		sprite_offset = { FIRE_LORD_BOSS_OFFSET_X,
						  FIRE_LORD_BOSS_OFFSET_Y };
		dead_sprite_offset = { FIRE_LORD_BOSS_OFFSET_DEAD_X ,
							   FIRE_LORD_BOSS_OFFSET_DEAD_Y };
		attack_power = 50;
		health = 130;
		name = "Fire Lord";
		resistance = AttackType::FIRE;
	};
	~FireLord() {};
};

