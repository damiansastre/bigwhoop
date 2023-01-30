#include <iostream>

#include "dungeon.h"
#include "action_response.h"
#include "player.h"
#include "room.h"
// consumables
#include "door.h"
#include "key.h"
#include "cake.h"
#include "treasure.h"
// weapons
#include "firemage.h"
#include "sword.h"
#include "firewand.h"
#include "electric_harp.h"
#include "waterpotion.h"

Dungeon::Dungeon()
{
}
Dungeon::~Dungeon()
{
    delete player;
}
// Gets the dungeon 
/*Room* Dungeon::GetCurrentRoom()
{
    return currentRoom;
}
*/

/*
Checks current game conditions
And end games if necesary.
*/
void Dungeon::CheckGameConditions()
{
    if (!player->IsAlive()){
        player->Kill();
        End(GameStatus::DEAD);
    }
    else
    {
        if (player->HasTreasure())
        {
            End(GameStatus::WIN);

        }
    }
}
/*
Executed when world is created in OLC Pixel Game Engine
Sets the Sprite tileset and starts the game
*/
bool Dungeon::OnUserCreate()
{
    tileset = new olc::Sprite("tileset.png");
    srand((int)time(0));

    StartGame();
    return true;
}
/*
Starts a DungeonCrawler game.
This methods handles initialization of player and rooms.
Also Creates a new instance of notifications in case it is a restart.
*/
void Dungeon::StartGame()
{
    player = new Player;
    Room* firstRoom = new Room(player);
    player->SetCurrentRoom(firstRoom);
    notifications = TArray<std::string>(10);
    AddNotification("Grab a Weapon");
    RenderGame();

}
// Restarts game.
void Dungeon::RestartGame()
{
    delete player;
    game_screen = GameScreen::PLAYING;
    game_status = GameStatus::PLAYING;
    StartGame();
}

/*
Handles game rendering based on game screen and game status.
*/
void Dungeon::RenderGame()
{
    Clear(olc::BLACK);
    switch (game_screen)
    {
    case GameScreen::PLAYING:
    {
        RenderInventory();
        RenderRoom();
        break;
    };
    case GameScreen::MENU:
    {
        RenderMenu();
        break;
    };
    case GameScreen::END:
    {
        RenderEndGame();
        if (game_status == GameStatus::DEAD) 
        {
            RenderInventory();
            RenderRoom();
        }
        break;
    }
    }
}

/* 
Handles Consume action by type
Placeholder method for when more consumables exist.
*/
ActionResponse Dungeon::HandleConsumeAction()
{
    ActionResponse action_response = player->Consume<Cake>();

    switch (action_response.action_type)
    {
    case ActionType::HEAL:
        player->Heal(action_response.value);
        break;
    }
    return action_response;
}
/*
Handles User input for weapon equipment.
*/
void Dungeon::HandleEquippedWeapon()
{
    if (!player->IsAlive())
    {
        return;
    }
    ActionResponse action_response = ActionResponse();
    if (GetKey(olc::Key::S).bHeld) {
        action_response = player->EquipWeapon<Sword>();
    }
    if (GetKey(olc::Key::W).bHeld) {
        action_response = player->EquipWeapon<FireWand>();
    }
    if (GetKey(olc::Key::Q).bHeld) {
        action_response = player->EquipWeapon<WaterPotion>();
    }
    if (GetKey(olc::Key::E).bHeld) {
        action_response = player->EquipWeapon<ElectricHarp>();
    }
    if (GetKey(olc::Key::C).bHeld) {
        action_response = HandleConsumeAction();
    }
    if (action_response.notification != "")
    {
        notifications.addElement(action_response.notification);
    }
}

/*
Handles user input for player movement.
*/
TVector2D<int> Dungeon::GetMovedPosition()
{
    TVector2D<int> newPosition = player->GetPosition();

    if (GetKey(olc::Key::LEFT).bHeld) {
        newPosition.x -= 1;
    }
    ;
    if (GetKey(olc::Key::RIGHT).bHeld) {
        newPosition.x += 1;

    }
    if (GetKey(olc::Key::UP).bHeld) {
        newPosition.y -= 1;
    }
    if (GetKey(olc::Key::DOWN).bHeld) {

        newPosition.y += 1;
    }
    return newPosition;
}

/*
Checks if the menu should be opened/closed based on user input
*/
bool Dungeon::HasToggleMenu()
{
 
    return GetKey(olc::Key::ESCAPE).bHeld;
}

// Checks whether the game should restart based on user input
bool Dungeon::ShouldRestart()
{

    return GetKey(olc::Key::SPACE).bHeld;
}

// Toggles Menu.
void Dungeon::ToggleMenu()
{
    if (game_screen == GameScreen::MENU)
    {
        game_screen = GameScreen::PLAYING;
    }
    else
    {
        game_screen = GameScreen::MENU;
    }
    
}

/*
Handles Frame update for OLC Pixel Game engine
*/
bool Dungeon::OnUserUpdate(float fElapsedTime)
{
    // Handles refresh rate, if not enough time has passed
    // since last refresh, returns in case time has not been enough
    fAccumulatedTime += fElapsedTime;
    if (fAccumulatedTime >= fTargetFrameTime)
    {
        fAccumulatedTime -= fTargetFrameTime;
        fElapsedTime = fTargetFrameTime;
    }
    else
        return true; // Don't do anything this frame
    // Checks if the user has toggled the menu
    if (HasToggleMenu())
    {
        ToggleMenu();
        return true;
    }
    // Checks if player restarted the game after dead.
    if (game_screen == GameScreen::END && ShouldRestart())
    {
        RestartGame();
        return true;
    }
    // 
   // if (!player->IsAlive())// && ShouldRestart())
   // {
    //    RenderEndGame();
    //}
    // Checks if user has equipped a weapon
    HandleEquippedWeapon();

    TVector2D<int> new_position = GetMovedPosition();
    ActionResponse action_response = player->HandleMoveAction(new_position);
    switch (action_response.action_type)
    {
    case ActionType::LOCKED:
        HandleLockedDoor(new_position, action_response);
        break;
    case ActionType::PICKUP:
        HandlePickUP(new_position, action_response);
        break; 
    case ActionType::MOVE_ROOM:
        HandleMoveRoom(new_position, action_response);
        break;
    case ActionType::ATTACK:
        HandleAttack(new_position, action_response);
        break;
    };
    if (action_response.notification != "")
    {
        AddNotification(action_response.notification);
    }
    if (action_response.should_move) {
        player->Move(new_position);
    }
    CheckGameConditions();
    RenderGame();
    return true;
}

// Handles Attack actions.
void Dungeon::HandleAttack(TVector2D<int> new_position, ActionResponse& action_response)
{
    Enemy* enemy = dynamic_cast<Enemy*>(player->GetCurrentRoom()->GetObjectByPosition(new_position));
    action_response = enemy->Attack(player);
    player->SetLastAttacked(enemy);
    if (!player->IsAlive())
    {
        action_response.notification = player->GetNotification();
    }
}

// Handles Item Pick UP actions.
void Dungeon::HandlePickUP(TVector2D<int> new_position, ActionResponse& action_response)
{
    Item* item = dynamic_cast<Item*>(player->GetCurrentRoom()->GetObjectByPosition(new_position));
    player->AddItemToInventory(item);
    player->GetCurrentRoom()->RemoveObject(item);
}

// Handles Changing of room actions
void Dungeon::HandleMoveRoom(TVector2D<int> new_position, ActionResponse& action_response)
{
    Door* door = dynamic_cast<Door*>(player->GetCurrentRoom()->GetObjectByPosition(new_position));
    EnterRoom(door, action_response);
}

// After a Locked or Room Move action
void Dungeon::EnterRoom(Door* door, ActionResponse& action_response)
{
    player->GetCurrentRoom()->RemoveObject(player);
    door->GetNextRoom()->AddObject(player);
    player->SetCurrentRoom(door->GetNextRoom());
    player->RemoveItemFromInventory(dynamic_cast<Item*>(door->GetKey()));
    player->SetPosition(player->GetOppositePosition(door->GetPosition(), door->GetNextRoom()->GetSize()));
}
/* Handles locked doors
    if A door is locked and the player has the corresponding key, open the door and move player to the next room.
    if the player does not have the key, display a room locked notification.
*/
void Dungeon::HandleLockedDoor(TVector2D<int> door_position, ActionResponse& action_response)
{
    Door* door = dynamic_cast<Door*>(player->GetCurrentRoom()->GetObjectByPosition(door_position));
    if (!player->HasKey(door->GetKey()))
    {
        return;
    }
    door->Unlock();
    Room* currentRoom = player->GetCurrentRoom();

    if (door->GetNextRoom() == nullptr)
    {
        Room* newRoom = new Room(player, door, currentRoom);
        door->SetNextRoom(newRoom);
        player->IncreaseRoomsVisited();
    }
    action_response.notification = "Entered a new Room";

    return EnterRoom(door, action_response);
}

// Renders a dungeon object.
bool Dungeon::RenderObject(TVector2D<int> position)
{
    MapObject* rendereable_object = player->GetCurrentRoom()->GetObjectByPosition(position);
    if (rendereable_object != nullptr)
    {
        if (rendereable_object->ShouldRender()) {
            RenderItemTile(rendereable_object->GetSpritePosition(), position);
            return true;
        }
    }
    return false;
}
// Renders Current room scene item (floor or wall tiles)
void Dungeon::RenderScene(TVector2D<int> position)
{
    if (position.x == 0 || position.y == 0 || position.x == player->GetCurrentRoom()->GetSize().x - 1 || position.y == player->GetCurrentRoom()->GetSize().y - 1)
    {
        RenderItemTile(player->GetCurrentRoom()->GetWallTile(), position);
    }
    else
    {
        RenderItemTile(player->GetCurrentRoom()->GetFloorTile(), position);
    }
}
// Renders a room tile by tile checking if an object should be rendered or a scene item.
void Dungeon::RenderRoom()
{    
    for (int y = 0; y < player->GetCurrentRoom()->GetSize().y; ++y)
    {
        for (int x = 0; x < player->GetCurrentRoom()->GetSize().x; ++x)
        {
            bool renderedTile = RenderObject({ x, y });

            if (!renderedTile) {
                RenderScene({ x, y });
            }
        }
    }
}