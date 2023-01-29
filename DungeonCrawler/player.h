#pragma once
#include "character.h"
#include "weapon.h"
class Key;
class Item;
class Room;
class Player : public Character
{
public:
	Player();
	~Player();
	
	// Inventory 
	int GetInventorySize();
	Item* GetInventoryItem(int position);
	TArray<std::string> GetInventoryNames();
	void AddItemToInventory(Item* item);
	void RemoveItemFromInventory(Item* item);

	bool HasTreasure();
	bool HasItem(Item* object);
	bool HasKey(Key* key); // this should be a template method.

	// Rooms
	int GetRoomsVisited();
	void IncreaseRoomsVisited();
	Room* GetCurrentRoom();
	void SetCurrentRoom(Room* room);
	TVector2D<int> GetOppositePosition(TVector2D<int> opposite, TVector2D<int> size);

	// Attacks
	virtual int GetAttackPower() override;
	virtual AttackType GetAttackType() override;
	virtual void Kill() override;

	//Movement 
	ActionResponse HandleMoveAction(TVector2D<int> newPosition);

	// Defining user Equip Weapon in header file so other classes know
	// how the template looks like. Otherwise raises unresolved
	// external symbol Exception
	template<typename W>
	ActionResponse EquipWeapon()
	{
		for (int index = 0; index < inventory.num(); ++index)
		{
			W* new_weapon = dynamic_cast<W*>(inventory.getElement(index));
			if (new_weapon != nullptr)
			{
				if (new_weapon != weapon)
				{
					weapon = new_weapon;
					sprite_offset = weapon->GetPlayerEquippedSprite();
					return { false, "Equipped " + weapon->GetName(), ActionType::NONE };
				}
			}
		}
		return { false, "", ActionType::NONE };
	};
	
private:
	TArray<Item*> inventory = TArray<Item*>(10);
	Weapon* weapon = nullptr;
	Room* currentRoom = nullptr;
	int roomsVisited = 0;
};

