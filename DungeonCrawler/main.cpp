#define OLC_PGE_APPLICATION
#include <iostream>

#include "dungeon.h"

int main()
{

	// Starts Dungeon and Game.
	Dungeon dungeon;
	if (dungeon.Construct(360, 240, 4, 4))
	{
		dungeon.Start();
	}
	return 0;
}
