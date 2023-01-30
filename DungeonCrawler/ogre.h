#include "boss.h"

class Ogre : public Boss
{
public:
	Ogre() {
		sprite_offset = { OGRE_BOSS_OFFSET_X,
					      OGRE_BOSS_OFFSET_Y };
		dead_sprite_offset = { OGRE_BOSS_OFFSET_DEAD_X ,
							   OGRE_BOSS_OFFSET_DEAD_Y };
		attack_power = 30;
		health = 150;
		name = "Ogre";
		resistance = AttackType::PHYSICAL;
	};
	~Ogre() {};
};

