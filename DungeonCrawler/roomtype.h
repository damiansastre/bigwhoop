#pragma once
#include <cstdint>

/*
Room Rendering sprice offset constants.
*/
constexpr int BRICK_WALL_X = 117;
constexpr int BRICK_WALL_Y = 39;
constexpr int BRICK_FLOOR_X = 156;
constexpr int BRICK_FLOOR_Y = 26;

constexpr int MUD_WALL_X = 0;
constexpr int MUD_WALL_Y = 39;
constexpr int MUD_FLOOR_X = 156;
constexpr int MUD_FLOOR_Y = 26;

constexpr int TREASURE_WALL_X = 39;
constexpr int TREASURE_WALL_Y = 39;
constexpr int TREASURE_FLOOR_X = 13;
constexpr int TREASURE_FLOOR_Y = 91;

constexpr int WOOD_WALL_X = 247;
constexpr int WOOD_WALL_Y = 39;
constexpr int WOOD_FLOOR_X = 234;
constexpr int WOOD_FLOOR_Y = 39;

/*
RoomTypes allow the room to be able to generate random
room types at creation.
*/
enum class RoomType : uint8_t
{
	BRICK,
	MUD,
	WOOD,
	TREASURE,
};