#pragma once
#include "player.h"
#include "room.h"

#include "key.h"
#include "treasure.h"

#include "weapon.h"

#include "player_sprite_offset.h"
#include "action_response.h"

Player::Player()
{
    sprite_offset = { PLAYER_SPRITE_OFFSET_X, PLAYER_SPRITE_OFFSET_Y };
    health = 100;
    attack_power = 10;
}
Player::~Player()
{
}

// Checks if the user has a treasure in their inventory.
bool Player::HasTreasure()
{
    for (int i = 0; i < inventory.num(); ++i)
    {
        Treasure* treasure = dynamic_cast<Treasure*>(inventory.getElement(i));
        if (treasure != nullptr)
        {
            return true;
        }
    }
    return false;
}

// Checks if a player has an item in the inventory.
bool Player::HasItem(Item* object)
{
    return inventory.contains(object);
}

// Adds an item to the inventory
void Player::AddItemToInventory(Item* item)
{
    if (!HasItem(item))
    {
        inventory.addElement(item);
    }
}

// Removes an item from inventory.
void Player::RemoveItemFromInventory(Item* item)
{
    if (inventory.contains(item))
    {
        inventory.removeElement(item);
    }
}

//Increases the amount of rooms visited.
void Player::IncreaseRoomsVisited()
{
    ++roomsVisited;
}
// Handles players move action.
ActionResponse Player::HandleMoveAction(TVector2D<int> newPosition)
{
    ActionResponse action;
    if (IsAlive())
    {
        // If the current position and the given position are the same. no movement required.
        if (!(newPosition == GetPosition()))
        {
            // Checks if given position is valid.
            if (GetCurrentRoom()->IsValidMovement(newPosition))
            {
                // Triggers the current tile action in the room.
                action = GetCurrentRoom()->TriggerTileAction(newPosition);
            }
        }
    }
    return action;
}
// Gets current player inventory size.
int Player::GetInventorySize()
{
    return inventory.num();
}

// Gets player amount of room's visited.
int Player::GetRoomsVisited()
{
    return roomsVisited;
}
// Checks if the player has a specific key.
bool Player::HasKey(Key* key)
{
    for (int i = 0; i < inventory.num(); ++i)
    {
        Key* newKey = dynamic_cast<Key*>(inventory.getElement(i));
        if (inventory.getElement(i) == key)
        {
            return true;
        }
    }
    return false;
}
// Gets an item from the inventory by position.
Item* Player::GetInventoryItem(int position)
{
    return inventory.getElement(position);
}
// Gets attack power based on resistance and weapon equipped.
int Player::GetAttackPower()
{
    int weapon_attack_power = 0;
    int res_attack_power = 0;
    if (weapon != nullptr)
    {
        weapon_attack_power = weapon->GetAttackPower();

        switch (weapon->GetAttackType())
        {
        case AttackType::ELECTRIC:
        {
            res_attack_power = attack_power + 10;
            break;
        }
        case AttackType::FIRE:
        {
            res_attack_power = attack_power + 20;
            break;
        }
        case AttackType::PHYSICAL:
        {
            res_attack_power = attack_power + 30;
            break;
        }
        case AttackType::WATER:
        {
            res_attack_power = attack_power + 40;
            break;
        }
        case AttackType::MAGIC:
        {
            res_attack_power = attack_power + 50;
            break;
        }
        }
    }
    return res_attack_power + weapon_attack_power;
}
// Gets current attack type.
AttackType Player::GetAttackType()
{
    AttackType atackT = attack_type;
    if (weapon != nullptr)
    {
        atackT = weapon->GetAttackType();
    }
    return atackT;
}
// Sets the current sprite to dead after the player is killed.
void Player::Kill()
{
    SetSprite({PLAYER_SPRITE_DEAD_OFFSET_X, PLAYER_SPRITE_DEAD_OFFSET_Y});
}

// Returns current Room.
Room* Player::GetCurrentRoom()
{
    return currentRoom;
}
// Sets player's current room.
void Player::SetCurrentRoom(Room* room)
{
    this->currentRoom = room;
}

// Gets the name of all items in the current inventory for display purposes.
TArray<std::string> Player::GetInventoryNames()
{
	TArray<std::string> names;
    for (int i = 0; i < inventory.num(); ++i)
    {
        Weapon* newWeapon = dynamic_cast<Weapon*>(inventory.getElement(i));
        if (newWeapon != nullptr) {
            std::string hotKey = newWeapon->GetHotKey();
            std::string weaponName = newWeapon->GetName();
            names.addElement( hotKey + ": equip " + weaponName);
        }
	}
	return names;
}

// When a player leaves a room, the position where the player spawns in the next roomm
// is based on the current position of the player. 
// So if the door where the player is leaving is at x=0, y=4, then the player should enter
// the next room from x=size_of_next_room, y=4.
TVector2D<int> Player::GetOppositePosition(TVector2D<int> opposite, TVector2D<int> size)
{
    int x = opposite.x;
    int y = opposite.y;
    if (opposite.x == 0)
    {
        x = size.x-1;
    }
    if (opposite.y == 0)
    {
        y = size.y-1;
    }
    if (opposite.x == size.x - 1)
    {
        x = 0;
    }
    if (opposite.y == size.y - 1)
    {
        y = 0;
    }
    return TVector2D<int>(x, y);
}
