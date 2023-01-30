#include "boss.h"

class ElectricChicken : public Boss
{
public:
	ElectricChicken() {
		sprite_offset = { ELECTRIC_CHICKEN_BOSS_OFFSET_X,
						  ELECTRIC_CHICKEN_BOSS_OFFSET_Y };
		dead_sprite_offset = { ELECTRIC_CHICKEN_BOSS_OFFSET_DEAD_X ,
							   ELECTRIC_CHICKEN_BOSS_OFFSET_DEAD_Y };
		attack_power = 40;
		health = 90;
		name = "Electric Chicken";
		resistance = AttackType::ELECTRIC;
	};
	~ElectricChicken() {};
};

