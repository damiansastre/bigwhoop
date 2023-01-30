#include "boss.h"
#include "player.h"

void Boss::SetResistance(AttackType resistance)
{
	this->resistance = resistance;
}

AttackType Boss::GetResistance()
{
	return resistance;
}

ActionResponse Boss::Attack(Player* player)
{
	int player_attack_power = player->GetAttackPower();
	AttackType attack_type = player->GetAttackType();
	if (attack_type == resistance)
	{
		player_attack_power -= 30;
	}
	Damage(player_attack_power);
	player->Damage(attack_power);
	return ActionResponse{ false, 0 , GetAttackNotification(player_attack_power, attack_power) , ActionType::NONE};
}