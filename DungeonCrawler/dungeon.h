#pragma once
#include "game_status.h"
#include "game_screen.h"
#include "game.h"

// Constants to handle framerate and action delay.
constexpr float TARGET_FRAME = 1.0f / 10.0f;
constexpr float ACCUMULATED_TIME = 1.0f;

/*
Dungeon
This class handles player input and actions.
*/
class Room;
class Door;
class Player;
class Dungeon : public Game
{
public:
    Dungeon();
    ~Dungeon();

    //Game Conditions
    void CheckGameConditions();

    //Rendering
    void RenderRoom();
    bool RenderObject(TVector2D<int> position);
    void RenderScene(TVector2D<int> position);
    void RenderGame();

    // Room Changing actions.
    //Room* GetCurrentRoom();
    TVector2D<int> GetMovedPosition();

    // User Actions
    void HandleEquippedWeapon();
    void HandleLockedDoor(TVector2D<int> new_position, ActionResponse& action_response);
    void HandlePickUP(TVector2D<int> new_position, ActionResponse& action_response);
    void HandleMoveRoom(TVector2D<int> new_position, ActionResponse& action_response);
    void HandleAttack(TVector2D<int> new_position, ActionResponse& action_response);
    void EnterRoom(Door* door, ActionResponse& action_response);
    ActionResponse HandleConsumeAction();

    // Menu Actions
    bool HasToggleMenu();
    void ToggleMenu();
    
    // Game State Actions
    bool ShouldRestart();
    void StartGame();
    void RestartGame();

    int roomCount = 1;

public:
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;

private:
    float fTargetFrameTime = TARGET_FRAME;
    float fAccumulatedTime = ACCUMULATED_TIME;
   // Room* currentRoom = nullptr;
};
