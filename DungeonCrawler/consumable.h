#pragma once
#include "item.h"

enum class ConsumableType : uint8_t
{
	CAKE,
	CONSUMABLE_NUM, // Easy way of getting the amount of enemies for random creation when creating a room
};

/*
Consumable
The consumable class allows players to pick up mapobjects from the world.
*/

class Consumable : public Item
{
public:
	Consumable();
	~Consumable();

	virtual void SetName(std::string name);
	virtual std::string GetName();
	
	virtual bool ShouldRender() override;
	
	virtual void PickUp();
	virtual bool IsPickedUp();

protected:
	std::string name;
	bool picked_up = false;
};