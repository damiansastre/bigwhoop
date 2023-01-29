#pragma once
#include "consumable.h"

/*
Treasure
This is the final object of the game, when picked up, the game ends.
*/
class Treasure : public Consumable
{
public:
	Treasure();
	~Treasure();
	virtual std::string GetNotification() override;
};