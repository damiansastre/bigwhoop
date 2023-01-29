#pragma once
#include <iostream>

/*
Action types refer to what the caller needs to execute when analysing an ActionResponse
*/
enum class ActionType : uint8_t
{
	NONE,
	PICKUP,
	LOCKED,
	UNLOCK,
	MOVE_ROOM,
	NEW_ROOM,
	ENEMY_KILLED,
	ATTACK
};

/*
Messaging struct for actions.
Every action in the game has a response
This is the way objects communicate with the Player/Room or Dungeon.
When an action is triggered, a MapObject returns an ActionResponse
Then is later analysed by the corresponding class to trigger a the corresponding events.
The idea behind this class is to make actions independent of the caller and based on the state of the object.
*/
struct ActionResponse
{
	bool should_move = false;
	std::string notification = "";
	ActionType action_type= ActionType::NONE;
};