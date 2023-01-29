#include "consumable.h"
Consumable::Consumable()
{
}
Consumable::~Consumable()
{

}
//Sets the Consumable name.
void Consumable::SetName(std::string name)
{
	this->name = name;
}
// Gets the consumable name
std::string Consumable::GetName()
{
	return name;
}
// Checks if the consumable should be rendered based on picked_up
bool Consumable::ShouldRender()
{
	return !picked_up;
}
// Picks and item Up
void Consumable::PickUp()
{
	picked_up = true;
}
// Checks if the consumable has been picked up
// DEPRECATED as items now leave the room when entering players inventory
// Leaving this logic for future implementations on whether the consumable
// should have extra logic based on pickup.
bool Consumable::IsPickedUp()
{
	return picked_up;
}