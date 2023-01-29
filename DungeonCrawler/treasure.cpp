#include "treasure.h"
#include "item_sprite_offset.h"

Treasure::Treasure()
{
	sprite_offset = { TREASURE_SPRITE_OFFSET_X , TREASURE_SPRITE_OFFSET_Y };
}

Treasure::~Treasure()
{
}

std::string Treasure::GetNotification()
{
	return "You Found Big Whoop";
}