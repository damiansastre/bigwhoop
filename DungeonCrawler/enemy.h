#pragma once
#include "character.h"
#include "enemy_sprite_offset.h"

/*
Setting up ENUM for easier access when creating random 
enemies in room logic. 
Adding ENEMY NUM allows us to register new enemies and 
be able to create them randomly from this enum.
*/
enum class EnemyType : uint8_t
{
	SKELETON,
	FIREMAGE,
	WATERMAGE,
	ELECTRICMAGE,
	ENEMY_NUM, // Easy way of getting the amount of enemies for random creation when creating a room
};

/*
Enemy
Enemies are a type of character that spawn in Dungeon's.
*/
class Enemy : public Character
{
public:
	Enemy();
	~Enemy();

	//Actions
	virtual ActionResponse Attack(Player* player);
	virtual ActionResponse TriggerAction() override;
	virtual std::string GetAttackNotification(int player_attack_power, int attack_power);
	virtual std::string GetNotification() override;
protected:
	std::string name;
	bool notified = false;
};