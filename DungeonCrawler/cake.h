#pragma once
#include "consumable.h"
#include "item_sprite_offset.h"

/*
Cake
Consumanle that allows players to heal by an amount.
*/
class Cake : public Consumable
{
public:
	Cake();
	Cake(std::string name, TVector2D<int> position);
	~Cake();
};