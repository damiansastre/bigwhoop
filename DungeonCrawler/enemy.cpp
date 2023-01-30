#include <string>

#include "enemy.h"
#include "player.h"
#include "action_response.h"
Enemy::Enemy()
{
}
Enemy::~Enemy()
{

}

ActionResponse Enemy::Attack(Player* player)
{
	int player_attack_power = player->GetAttackPower();
	Damage(player_attack_power);
	player->Damage(attack_power);
	return ActionResponse{ false, 0,  GetAttackNotification(player_attack_power, attack_power) , ActionType::NONE };
}

ActionResponse Enemy::TriggerAction()
{
	if (!IsAlive()) {
		return ActionResponse{ false, 0,  "", ActionType::NONE };
	}
	return ActionResponse{ false, 0,  "",  ActionType::ATTACK};
}
std::string Enemy::GetAttackNotification(int player_attack_power, int attack_power)
{
	std::string notification =  "ATTACKED " + std::to_string(player_attack_power) + " RECEIVED " + std::to_string(attack_power);
	if (!IsAlive())
	{
		notification = "You Killed " + this->name;
	}
	return notification;
}
std::string Enemy::GetNotification()
{
	return "You Killed " + name;
}