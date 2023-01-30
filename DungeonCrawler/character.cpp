#include "character.h"

Character::Character()
{
}
Character::~Character()
{
}
// Moves Character to a position
void Character::Move(TVector2D<int> position)
{
	this->position = this->position + position;
}
// Gets Character attack power
int Character::GetAttackPower()
{
	return attack_power;
}
// Gets Character AttackType
AttackType Character::GetAttackType()
{
	return attack_type;
}
// Gets player Attack description for ingame notifications
std::string Character::GetAttackTypeDescription(AttackType attack_type)
{
    std::string attack_description = "";
    switch(attack_type)
    {
	    case AttackType::ELECTRIC:
        {
            attack_description = "ELECTRIC";
            break;
        }
        case AttackType::FIRE:
        {
            attack_description = "FIRE";
            break;
        }
        case AttackType::WATER:
        {
            attack_description = "WATER";
            break;
        }
        case AttackType::MAGIC:
        {
            attack_description = "MAGIC";
            break;
        }
        default:
        {
            attack_description = "PHYSICAL";
            break;
        }

    }
    return attack_description;


}

// Sets the current sprit offset
void Character::SetSprite(TVector2D<int> spritePosition)
{
	this->sprite_offset = spritePosition;
}

// This next 2 methods could be defined as 1 and change the damage to be either positive or negative.
// TODO.
// Damages the character
void Character::Damage(int damage)
{
	health -= damage;
    if (health < 0)
    {
        Kill();
    }

}
// Heals the character
void Character::Heal(int heal)
{
	health += heal;
}
// Checks if player is alive
bool Character::IsAlive()
{
	return health > 0;
}
// Gets player health
int Character::GetHealth()
{
	return health;
}
// Sets the Characters dead sprite for rendering.
void Character::Kill()
{
    SetSprite(dead_sprite_offset);
}

