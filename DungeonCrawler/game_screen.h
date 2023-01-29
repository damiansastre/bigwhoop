#pragma once
#include <cstdint>
/*
Game Screens correspond to what screen the Game object should render
based on the current game state.
*/
enum class GameScreen :uint8_t
{
	INTRO,
	MENU,
	PLAYING,
	END
};