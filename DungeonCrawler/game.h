#pragma once
#include <iostream>

#include "olcPixelGameEngine.h"

#include "tvector2d.h"
#include "player.h"
#include "game_status.h"
#include "game_screen.h"

/*
Implements Rendering for PixelGameEngine.
*/
class Game : public olc::PixelGameEngine
{
public:

	Game();
	~Game();

	// Rendering
	void SetTileSet(olc::Sprite* tileset);
	void RenderTextTile(std::string text, TVector2D<int> position);
	void RenderItemTile(TVector2D<int>& spritePosition, TVector2D<int> position);
	void RenderEnemyHealth();
	void RenderInventory();
	void RenderInventoryItems();
	void RenderPlayerStats();
	void RenderNotifications();
	void RenderRestart();
	void RenderMenu();
	virtual void RenderEndGame();

	// Game Status checks.
	GameStatus GetGameStatus(); 
	void SetGameStatus(GameStatus game_status);
	void SetGameScreen(GameScreen game_screen);

	// Notifications
	void AddNotification(std::string notification);

	// Player accesors
	void SetPlayer(Player* player);
	Player* GetPlayer();
	void End(GameStatus game_status);

private:
	Game(Game& In);

protected:
	olc::Sprite* tileset;

	Player* player = nullptr;

	GameStatus game_status = GameStatus::PLAYING; // Start both screen and status as PLAYING.
	GameScreen game_screen = GameScreen::PLAYING; // TODO: Implement Intro.

	TArray<std::string> notifications = TArray<std::string>(10);
};
