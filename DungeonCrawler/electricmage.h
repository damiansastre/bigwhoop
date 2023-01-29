#pragma once
#include "enemy.h"

/*
ElectricMage 
*/
class ElectricMage : public Enemy
{
public:
	ElectricMage() {

		sprite_offset = { ELECTRIC_MAGE_OFFSET_X,
										 ELECTRIC_MAGE_OFFSET_Y };
		dead_sprite_offset = { ELECTRIC_MAGE_OFFSET_DEAD_X ,
									 ELECTRIC_MAGE_OFFSET_DEAD_Y };
		attack_power = 30;
		health = 100;
		name = "Electric Mage";
	};
	~ElectricMage();
};

