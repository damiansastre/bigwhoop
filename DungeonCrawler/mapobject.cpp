#include "mapobject.h"
#include "tvector2d.h"
#include "player.h"
#include "dungeon.h"
#include "action_response.h"
MapObject::MapObject()
{
}

MapObject::~MapObject()
{
}

/*Checks whether two objects are the same based on IDS
 TODO: THIS IS HEAVILY DEPENDANT ON RANDOM IDS() which the game is
 currently not supporting uniqueness. 
*/
bool MapObject::operator==(const MapObject& other)
{
	return this->id == other.id;
}
// Sets the position in the game for an object
void MapObject::SetPosition(TVector2D<int> position)
{
	this->position = position;
}
// Gets object position.
TVector2D<int> MapObject::GetPosition()
{
	return position;
}
// Checks if the given position is equal to the current position.
bool MapObject::IsPosition(TVector2D<int> position)
{
	return this->position == position;
}

// Checks whether the object should be rendered or not
bool MapObject::ShouldRender()
{
	return true;
}
// Triggers a map object action.
ActionResponse MapObject::TriggerAction()
{
	return ActionResponse{ true, "", ActionType::NONE };
}

// Gets the current sprite position.
TVector2D<int>& MapObject::GetSpritePosition()
{
	return sprite_offset;
}

// Gets the item notification.
std::string MapObject::GetNotification()
{
	return notification;
}

// Gets the current object ID.
int MapObject::GetID()
{
	return id;
}
