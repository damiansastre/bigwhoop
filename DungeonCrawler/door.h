#pragma once
#include "item.h"

/*
Door 
Object that handles communication between Rooms.
*/
class Key;
class Room;
class Door : public Item
{
public:
	Door();
	~Door();

	Key* GetKey();

	// Movement
	void SetKey(Key* key);
	Room* GetNextRoom();
	virtual ActionResponse TriggerAction() override;
	void SetNextRoom(Room* room);

	//Actions
	bool Closed();
	void Unlock();

private:
	bool locked = true;
	Door* sibling_door = nullptr;
	Room* next_room = nullptr;
	Key* key = nullptr;
};