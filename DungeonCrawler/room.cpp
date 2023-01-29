#include "room.h"
#include "dungeon.h"
#include "player.h"

#include "treasure.h"
#include "key.h"
#include "door.h"
#include "cake.h"

#include "skeleton.h"
#include "ogre.h"
#include "electricmage.h"
#include "firemage.h"
#include "watermage.h"

#include "electric_harp.h"
#include "firewand.h"
#include "waterpotion.h"
#include "sword.h"

// Gets random values by range. This implementation allows the game to create 
// Items based on a random amount needed between a range.
int GetRandomByRangeR(int rangeMin, int rangeMax)
{
	return (double(rand()) / RAND_MAX) * (rangeMax - rangeMin) + rangeMin;
}

Room::Room()
{

}
/*
Creates a room for a player for the first time when a game is started
*/
Room::Room(Player* player)
{
	// Adds player as object of the room
	AddObject(player);
	// Sets player position
	player->SetPosition(TVector2D<int>(5, 5));
	// First room includes all the weapons available in the game, render them so the player can pick them up.
	CreateItem<Sword>(TVector2D<int>(3, 3), TVector2D<int>(3, 3));
	CreateItem<WaterPotion>(TVector2D<int>(4, 3), TVector2D<int>(4, 3));
	CreateItem<FireWand>(TVector2D<int>(5, 3), TVector2D<int>(5, 3));
	CreateItem<ElectricHarp>(TVector2D<int>(6, 3), TVector2D<int>(6, 3));
	// Create the first door.
	int doorPosition = CreateItem<Door>(TVector2D<int>(1, 1), TVector2D<int>(8, 8));
	int keyPosition = this->CreateItem<Key>(TVector2D<int>(7, 7), TVector2D<int>(7, 7));
	Key* key = dynamic_cast<Key*>(GetObjectByIndex(keyPosition));
	Door* door = dynamic_cast<Door*>(GetObjectByIndex(doorPosition));
	door->SetKey(key);
	// Set the first room as random.
	SetRandomRoomType(player->GetRoomsVisited());
}

/*
Creates a new room based on a door and a room.
*/
Room::Room(Player* player, Door* oldDoor, Room* oldRoom)
{
	// Sets the player to the opposite location ( see palyer GetOppositePosition for more information)
	player->SetPosition(player->GetOppositePosition(oldDoor->GetPosition(), size));
	// Create a new door in the new room opposite to the current door.
	Door* door = new Door;
	door->SetPosition(player->GetPosition());
	door->SetNextRoom(oldRoom);
	door->SetKey(oldDoor->GetKey());
	door->Unlock();
	AddObject(door);
	// Add player to the new room
	AddObject(player);
	// Create the new room.
	CreateRoom(player);
}
// Sets a random room type for the current room being created.
// If the player has visited enough rooms, attempt to get the finished room.
RoomType Room::SetRandomRoomType(int roomsVisited)
{
	RoomType roomType{};
	// TODO: This should be a constant.
	if (roomsVisited > 5 && ((rand() % 2) == 1)) {
		roomType = RoomType::TREASURE;
	}
	else {
		roomType = RoomType(GetRandomByRangeR(0, 2));
	}
	// Set the room Type.
	SetRoomType(roomType);
	return roomType;
}
/*
Create a room for a given player.
*/
void Room::CreateRoom(Player* player)
{
	RoomType roomType = SetRandomRoomType(player->GetRoomsVisited());
	if (roomType == RoomType::TREASURE) {
		CreateItem<Treasure>(TVector2D<int>(4, 4), TVector2D<int>(4, 4));
		return;
	}
	CreateDoors();
	CreateConsumables();
	CreateEnemies();
	CreateBoss();

}
// When deleting a room we should delete all the items inside of it.
Room::~Room()
{
	for (int index= 0; index < items.num(); ++index)
	{
		items.removeElement(index);
	}
}
// Create randomly located doors.
void Room::CreateDoors()
{
	int num_doors = GetRandomByRangeR(1, max_doors);
	int key_position = this->CreateItem<Key>(door_lower_boundaries, door_upper_boundaries);

	Key* key = dynamic_cast<Key*>(GetObjectByIndex(key_position));
	for (int key_index = 0; key_index < num_doors; key_index++)
	{
		int door_position = CreateItem<Door>(door_lower_boundaries, door_upper_boundaries);
		Door* door = dynamic_cast<Door*>(GetObjectByIndex(door_position));
		door->SetKey(key);
	}
}
// Create a randomly located boss
void Room::CreateBoss()
{
	int boss_index = GetRandomByRangeR(0, static_cast<int>(BossType::BOSS_NUM));
	switch (static_cast<BossType>(boss_index))
	{
	case BossType::OGRE:
		CreateItem<Ogre>(item_lower_boundaries, item_upper_boundaries);
		break;


	}
}
// Create randomly located consumables.
void Room::CreateConsumables()
{
	int consumable_amount = GetRandomByRangeR(0, 2);
	for (int consumable_index = 0; consumable_index < consumable_amount; ++consumable_index)
	{
		int consumableIndex = GetRandomByRangeR(0, static_cast<int>(ConsumableType::CONSUMABLE_NUM));
		switch (static_cast<ConsumableType>(consumableIndex))
		{
		case ConsumableType::CAKE:
			CreateItem<Cake>(item_lower_boundaries, item_upper_boundaries);
		}
	}
}
// Create randomly located enemies.
void Room::CreateEnemies()
{

	int enemyAmount = GetRandomByRangeR(1, 2);
	for (int i = 0; i < enemyAmount; ++i)
	{
		int enemyIndex = GetRandomByRangeR(0, static_cast<int>(EnemyType::ENEMY_NUM));
		switch (static_cast<EnemyType>(enemyIndex))
		{
		case EnemyType::FIREMAGE:
			CreateItem<FireMage>(item_lower_boundaries, item_upper_boundaries);
			break;
		case EnemyType::WATERMAGE:
			CreateItem<WaterMage>(item_lower_boundaries, item_upper_boundaries);
			break;
			
		case EnemyType::ELECTRICMAGE:
			CreateItem<ElectricMage>(item_lower_boundaries, item_upper_boundaries);
			break;
		case EnemyType::SKELETON:
			CreateItem<Skeleton>(item_lower_boundaries, item_upper_boundaries);
			break;

		}
	}
}
// Checcks if the current location is valid and empty.
bool Room::IsValidItemLocation(const TVector2D<int> location, MapObject* object)
{
	if ((location.x == 0 && location.y == 0) || 
		(location.x == 0 && location.y == size.y) ||
		(location.x == size.x && location.y == 0) ||
		(location.x == size.x && location.y == size.y))
	{
		return false;
	}
	if (location.x == 0 || location.y == 0 || location.x == size.x || location.y == size.y)
	{
		return false;
	}
	
	Door* door = dynamic_cast<Door*>(object);
	if (door != nullptr)
	{
		if (location.x == 0)
		{
			if (!(location.y > 0 && location.y < size.y))
			{
				return false;
			}
		}
		if (location.y == 0)
		{
			if (!(location.y > 0 && location.y < size.y))
			{
				return false;
			}
		}
	}
		
	for (int i = 0; i < items.num(); ++i)
	{
		if (items.getElement(i)->IsPosition(location))
		{
			return false;
		}
	}
	return true;

}
// Gets a random Location for a door given the door boundaries set in the class.
TVector2D<int> Room::GetRandomDoorLocation()
{
	
	int x = 0;
	int y = 0;
	int axis = GetRandomByRangeR(0, 2);

	if (axis == 0)
	{
		x = GetRandomByRangeR(0, 2);
		if (x != 0)
		{
			x = size.x-1;
		}
		y = GetRandomByRangeR(1, size.y-1);
	}
	else
	{
		y = GetRandomByRangeR(0, 2);
		if (y != 0)
		{
			y = size.y-1;
		}
		x = GetRandomByRangeR(1, size.x-1);
		std::cout << "X   : " << x << std::endl;

	}
	return { x, y };
}
// Attempts to get a valid location until it finds one.
// TODO: This logic could lead to a endless loop if the room is already full.
// Current implementation of the game is only adding a specific amount of items that never get to this point.
// There should be a safeguard in place for the amount of items a room could have in the future.
TVector2D<int> Room::GetValidLocation(TVector2D<int> lowerBound, TVector2D<int> upperBound, MapObject* object)
{
	TVector2D<int> validLocation = TVector2D<int>(0, 0);
	do
	{	
		Door* door = dynamic_cast<Door*>(object);
		if (door != nullptr)
		{
			validLocation = GetRandomDoorLocation();
		}
		else
		{
			validLocation= TVector2D<int>(GetRandomByRangeR(lowerBound.x, upperBound.x), GetRandomByRangeR(lowerBound.y, upperBound.y));
		}

	} while (!IsValidItemLocation(validLocation, object));
	return validLocation;
}
// Template function to create Items based on class.
template<typename T>
int Room::CreateItem(TVector2D<int> lowerBound, TVector2D<int> upperBound)
{
	T* item = new T;
	item->SetPosition(GetValidLocation(lowerBound, upperBound, item));
	items.addElement(item);
	return items.num()-1;
}
// Sets the room Size
void Room::SetSize(TVector2D<int> position)
{
	this->size = position;
}

// Gets the Room size.
TVector2D<int> Room::GetSize()
{
	return size;
}

// Adds an object to the room
void Room::AddObject(MapObject* object)
{
	items.addElement(object);
}

// REmoves an object from the room
void Room::RemoveObject(MapObject* object)
{
	int index = items.getElementIndex(object);
	items.removeElement(object);
}

/*
Triggers a specific tile action and returns the corresponding ActionResponse for it
*/
ActionResponse Room::TriggerTileAction(TVector2D<int> position)
{
	ActionResponse action;
	for (int itemPosition = 0; itemPosition < items.num(); ++itemPosition)
	{
		if (items.getElement(itemPosition)->IsPosition(position))
		{
			return items.getElement(itemPosition)->TriggerAction();
		}
	}
	return ActionResponse{ true , "", ActionType::NONE };
}
// Sets the room Type
void Room::SetRoomType(RoomType room_type)
{
	switch (room_type)
	{
	case RoomType::BRICK:
		SetWallTile({ BRICK_WALL_X, BRICK_WALL_Y });
		SetFloorTile({BRICK_FLOOR_X, BRICK_FLOOR_Y});
		break;
	case RoomType::MUD:
		SetWallTile({MUD_WALL_X, MUD_WALL_Y});
		SetFloorTile({MUD_FLOOR_X, MUD_FLOOR_Y});
		break;
	case RoomType::TREASURE:
		SetWallTile({TREASURE_WALL_X, TREASURE_WALL_Y});
		SetFloorTile({TREASURE_FLOOR_X, TREASURE_FLOOR_Y});
		break;
	default:
		SetWallTile({WOOD_WALL_X, WOOD_WALL_Y});
		SetFloorTile({WOOD_FLOOR_X, WOOD_FLOOR_Y});
	};
}

// Sets the room Floor Tile
void Room::SetFloorTile(TVector2D<int> floorTile)
{
	this->floorTile = floorTile;
}
// Sets the room Wall Tile
void Room::SetWallTile(TVector2D<int> position)
{
	this->wallTile = position;
}

// Checks whether it is a valid movement based on item location and doors.
bool Room::IsValidMovement(TVector2D<int> position)
{
	for (int i = 0; i < items.num(); ++i)
	{
		Door* door = dynamic_cast<Door*>(items.getElement(i));
		if (door != nullptr)
		{
			if (door->IsPosition(position))
			{
				return true;
			}
		}
	}
	if (position.x >= 1 && position.x < this->size.x-1 && position.y >= 1 && position.y < this->size.y -1)
	{
		return true;
	}
	return false;
}
// Retursn an object by index
MapObject* Room::GetObjectByIndex(int index)
{
	return items.getElement(index);
}

// Returns an object by position
MapObject* Room::GetObjectByPosition(TVector2D<int> position)
{
	for (int item_index = 0; item_index < items.num(); ++item_index)
	{
		MapObject* obj = items.getElement(item_index);
		if (items.getElement(item_index)->GetPosition() == position)
		{
			return items.getElement(item_index);
		}

	}
	return nullptr;
}

// Check if the room already has an object
bool Room::HasObject(MapObject* object)
{
	return items.contains(object);
}

// Gets the room type
RoomType Room::GetRoomType()
{
	return this->room_type;
}
// Gets the amount of items in the room
int Room::GetNumObjects()
{
	return items.num();
}

// Gets the room's floor tile
TVector2D<int>& Room::GetFloorTile()
{
	return floorTile;
}

// Gets the room's wall tile.
TVector2D<int>& Room::GetWallTile()
{
	return wallTile;
}
