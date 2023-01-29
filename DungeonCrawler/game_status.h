#pragma once
#include <stdint.h>

/*
Game Status allow the Game object to manage game states.
*/
enum class GameStatus : uint8_t
{
	PLAYING,
	WIN,
	DEAD
};