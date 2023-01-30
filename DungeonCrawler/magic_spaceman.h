#pragma once
#include "boss.h"

class MagicSpaceman : public Boss
{
public:
	MagicSpaceman() {
		sprite_offset = { MAGIC_SPACEMAN_BOSS_OFFSET_X,
						  MAGIC_SPACEMAN_BOSS_OFFSET_Y };
		dead_sprite_offset = { MAGIC_SPACEMAN_BOSS_OFFSET_DEAD_X ,
							   MAGIC_SPACEMAN_BOSS_OFFSET_DEAD_Y };
		attack_power = 20;
		health = 110;
		name = "Magic Spaceman";
		resistance = AttackType::MAGIC;
	};
	~MagicSpaceman() {};
};

