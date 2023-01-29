#pragma once
#include "enemy.h"

/*
Skeleton
*/
class Skeleton : public Enemy
{
public:
	Skeleton()
	{
		sprite_offset = { SKELETON_OFFSET_X, SKELETON_OFFSET_Y };
		dead_sprite_offset = { SKELETON_OFFSET_DEAD_X, SKELETON_OFFSET_DEAD_Y };
		attack_power = 10;
		health = 30;
		name = "Skeleton";
	}
	~Skeleton();
};