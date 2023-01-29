#include "door.h"
#include "player.h"
#include "room.h"
#include "key.h"
#include "dc_const.h"

Door::Door()
{
	sprite_offset = TVector2D<int>(DOOR_SPRITE_OFFSET_X, DOOR_SPRITE_OFFSET_Y);
}
Door::~Door()
{

}
// Gets Next Room for the current door
Room* Door::GetNextRoom()
{
	return next_room;
}
// Sets the current door's key
void Door::SetKey(Key* key)
{
	this->key = key;
}
// Checks whether a door is closed.
bool Door::Closed()
{
	return locked;
}
// Unlocks a door
void Door::Unlock()
{
	locked = false;
}
// Gets the door's key
Key* Door::GetKey()
{
	return key;
}

// Sets Next room for the current door
void Door::SetNextRoom(Room* room)
{
	next_room = room;
}
/*
This action returns LOCKED action type in case the door has not yet been unlocked
Is up to the game to decide whether to unlock it or leave locked.
If the door is not unlocked, let the user move to the next room.
*/
ActionResponse Door::TriggerAction()
{
	if (Closed())
	{
		return ActionResponse{ false, "Door is Locked", ActionType::LOCKED };
	}
	
	return { false, "You Entered a new Room", ActionType::MOVE_ROOM};	
}

