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
	std::cout << "ATTACKED: " << player_attack_power << std::endl;
	std::cout << "RECEIVED: " << attack_power << std::endl;
	return ActionResponse{ false, "You attacked", ActionType::NONE };
}

ActionResponse Enemy::TriggerAction()
{
	if (!IsAlive()) {
		Kill();	
		return ActionResponse{ false, GetNotification(), ActionType::ENEMY_KILLED };
	}
	return ActionResponse{ false, "Enemy Attacked",  ActionType::ATTACK};
}
std::string Enemy::GetNotification()
{
	return "Attacked " + name;

}