#pragma once
#include "tvector2d.h"
#include "roomtype.h"
#include "action_response.h"
#include "mapobject.h"
class Dungeon;
class Door;
class Player;
class MapObject;

/* 
Room
Rooms in DungeonCrawler handle item positioning and movement for players.
*/
class Room 
{
public:
    Room();
    Room(Player* player);
    Room(Player* player, Door* door, Room* room);
    ~Room();

    // initialization 
    void CreateRoom(Player* player);
    void SetSize(TVector2D<int> position);
    TVector2D<int> GetSize();
    void SetFloorTile(TVector2D<int> position);
    void SetWallTile(TVector2D<int> position);
    RoomType SetRandomRoomType(int roomsVisited);
    RoomType GetRoomType();
    TVector2D<int>& GetFloorTile();
    TVector2D<int>& GetWallTile();

    // validators
    bool IsValidItemLocation(const TVector2D<int> position, MapObject* object);
    bool IsValidMovement(TVector2D<int> position);
    TVector2D<int> GetValidLocation(TVector2D<int> lowerBound, TVector2D<int> upperBound, MapObject* object);
    TVector2D<int> GetRandomDoorLocation();

    // object creators
    template<typename T>
    int CreateItem(TVector2D<int> lowerBound, TVector2D<int> upperBound);
    void AddObject(MapObject* item);
    void RemoveObject(MapObject* item);
    void CreateEnemies();
    void CreateConsumables();
    void CreateDoors();
    void CreateBoss();

    // actions
    ActionResponse TriggerTileAction(TVector2D<int> position);
    void SetRoomType(RoomType roomType);
    MapObject* GetObjectByIndex(int index);
    MapObject* GetObjectByPosition(TVector2D<int> position);
    bool HasObject(MapObject* object);
	int GetNumObjects();

private:
    TArray<MapObject*> items = TArray<MapObject*>(10);
    TVector2D<int> size = { 10, 10 };
    TVector2D<int> position;
    TVector2D<int> wallTile = { 0, 0 };
    TVector2D<int> floorTile = { 0, 0 };
    TVector2D<int> item_lower_boundaries = { 2, 2 };
    TVector2D<int> item_upper_boundaries = { 8, 8 };
    TVector2D<int> door_lower_boundaries = { 1, 1 };
    TVector2D<int> door_upper_boundaries = { 8, 8 };
    int max_doors = 3;
    RoomType room_type = RoomType::WOOD;
};