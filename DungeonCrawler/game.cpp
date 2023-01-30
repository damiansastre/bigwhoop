#include "game.h"
#include "boss.h"
#include "item.h"
#include "player.h"
#include "dc_const.h"
#include "game_status.h"

Game::Game()
{
    delete tileset;
    delete player;
}

Game::~Game()
{

}
// Sets the current game TileSet
void Game::SetTileSet(olc::Sprite* tileset)
{
    tileset = tileset;
}
// Sets the current Game status
void Game::SetGameStatus(GameStatus gameStatus)
{
    this->game_status = gameStatus;
}
// Sets the current game screen
void Game::SetGameScreen(GameScreen game_screen)
{
    this->game_screen = game_screen;
}
// Gets the current game status
GameStatus Game::GetGameStatus()
{
    return  game_status;
}
// Sets the current player
void Game::SetPlayer(Player* pl)
{
    player = pl;
}
// Gets the current player.
Player* Game::GetPlayer()
{
    return player;
}
// Ends the game, displays end screen.
void Game::End(GameStatus game_status)
{
    SetGameStatus(game_status);
    SetGameScreen(GameScreen::END);
}

// Adds a notification to the notification engine.
void Game::AddNotification(std::string notification)
{
    notifications.addElement(notification);
}
// Renders a Text file based on positions.
// This heavily depends on 'tileset.png' provided by the package.
// Handles UPPERCASE and LOWERCASE LETTERS, NUMBERS and Specific symbols.
void Game::RenderTextTile(std::string text, TVector2D<int> initial_position)
{
  //  const olc::vi2d spriteSize(PIXEL_SIZE, PIXEL_SIZE);
    int startingY = MENU_STARTING_Y;
    int x = 0;
    int y = 0;
    int yOffset = 0;
    for (int i = 0; i <= text.length() - 1; ++i)
    {
        int position = text[i];
        if (position >= 0)
        {
            yOffset = 0;
            x = position % MENU_A;

            if (position >= MENU_A && position < MENU_T)
            {
                if (position > MENU_X && position < MENU_T) {
                    x = x % 20;
                    yOffset +=1;
                }
            }
            else if (position >= MENU_T && position < MENU_SUB_1)
            {
                yOffset = 1;
                if (position >= MENU_T && position <= MENU_SUB_2) {
                    x = x % MENU_MOD_1;
                }
                else
                {
                    x = x % MENU_MOD_2;
                    yOffset += 1;
                }
            }
            else if (position == MENU_EQ_1)
            {
                x = 0;
                yOffset = -2;
            }
            else if (position == MENU_EQ_2)
            {
                x = 21;
                yOffset = 2;
            }
            else if (position == MENU_EQ_3)
            {
                x = 0;
                yOffset = 3;
            }
            else if (position >= MENU_EQ_4 && position <= MENU_EQ_5)
            {
                x = position - MENU_SUB_3;
                if (position >= MENU_SUB_4)
                {
                    yOffset += 1;
                    x -= 5;
                }
                else if (position == MENU_SUB_5)
                {
                    yOffset += 1;
                    x += 5;
                }
            }

            y = startingY + (yOffset * PIXEL_SIZE) + yOffset;
            TVector2D<int> off_set = { x * PIXEL_SIZE + x, y };
            TVector2D<int> sprite_position = { initial_position.x + i, initial_position.y };
            RenderItemTile(off_set, sprite_position);
        }


    }
}

// Renders a tile based on sprite offset and position in the game screen.
void Game::RenderItemTile(TVector2D<int>& item_sprite_offset, TVector2D<int> initial_position)
{
    const olc::vi2d spriteSize(PIXEL_SIZE, PIXEL_SIZE);
    const olc::vi2d spriteOffset(item_sprite_offset.x, item_sprite_offset.y);
    const olc::vi2d spritePosition((initial_position.x * PIXEL_SIZE) + initial_position.x, initial_position.y* PIXEL_SIZE);
    DrawPartialSprite(spritePosition, tileset, spriteOffset, spriteSize);
}

//Render player's inventory items
void Game::RenderInventoryItems()
{
    DrawLine(120, 45, ScreenWidth(), 45, olc::BLUE);

    // Player Items
    RenderTextTile("INVENTORY", { 10, 8 });
    int inventoryPadding = 0;
    int itemCounter = 0;
    for (int i = 0; i < player->GetInventorySize(); ++i)
    {
        if (i % 10 == 0)
        {
            inventoryPadding += 1;
            itemCounter = 0;
        }
        RenderItemTile(player->GetInventoryItem(i)->GetSpritePosition(), { 10 + itemCounter, 8 + inventoryPadding });
        itemCounter += 1;
    }
}

// Render Player Stats
void Game::RenderPlayerStats()
{
    // Player Stats
    std::string health = "HEALTH        ";
    health += std::to_string(GetPlayer()->GetHealth());
    std::string atk = "ATK           ";
    atk += std::to_string(GetPlayer()->GetAttackPower());
    std::string atkType = "ATK TYPE ";
    atkType += GetPlayer()->GetAttackTypeDescription(player->GetAttackType());

    RenderTextTile(health, { 10, 0 });
    RenderTextTile(atk, { 10, 1 });
    RenderTextTile(atkType, { 10, 2 });
}

// Render Notifications
void Game::RenderNotifications()
{
    RenderTextTile("Activity Log", { 0, 11 });

    // Notifications.
    if (notifications.num() > 0)
    {
        for (int i = notifications.num() - 1; i >= 0; --i)
        {
            RenderTextTile(notifications.getElement(i), { 0, 10 + (notifications.num() - i) });
        }
    }

}

// Render Game restart menu
void Game::RenderRestart()
{
    if (!player->IsAlive())
    {
        RenderTextTile("Press spacebar to restart", { 0, 15 });

    }
}
// Renders player inventory window
void Game::RenderInventory()
{
    RenderPlayerStats();
    RenderEnemyHealth();
    RenderInventoryItems();
    RenderNotifications();
    RenderRestart();
}

void Game::RenderEnemyHealth()
{
    Enemy* last_attacked = player->GetLastAttacked();
    if (last_attacked != nullptr)
    {
        RenderTextTile("ENEMY", { 10, 4 });

        int health = last_attacked->GetHealth();
        if (health > 0)
        {
            RenderTextTile("HEALTH      " + std::to_string(health), { 10, 5 });
            Boss* boss = dynamic_cast<Boss*>(last_attacked);
            std::string resistance = "None";
            if (boss != nullptr)
            {
                resistance = boss->GetAttackTypeDescription(boss->GetResistance());
            }
            RenderTextTile("RES       " + resistance, { 10, 6 });

        }
    }
}

// Renders menu
void Game::RenderMenu()
{
    RenderTextTile("Big Whoop Crawler Menu", { 4, 0 });
    RenderTextTile("Find Big Whoop to win", { 2, 3 });
    RenderTextTile("Grab Keys to open Doors", { 2, 4 });

    TVector2D<int> treasure = TVector2D<int>(559, 533);
    RenderItemTile(treasure, { 1, 3 });
    RenderItemTile(treasure, { 22, 3 });
    RenderTextTile("Weapon                 Key", { 2, 6 });
    RenderTextTile("Mighty Pirate Sword     S", { 2, 7 });
    RenderTextTile("Fire Wand               W", { 2, 8 });
    RenderTextTile("Water potion            Q", { 2, 9 });
    RenderTextTile("Electric Harp           E", { 2, 10 });
    RenderTextTile("Consumable               ", { 2, 11 });
    RenderTextTile("Cake                    C", { 2, 12 });

    RenderTextTile("Press ESC to return      ", { 2, 14 });
}

// Renders Game End.
void Game::RenderEndGame()
{
    if (game_status == GameStatus::WIN)
    {
        RenderTextTile("CONGRATULATIONS ", { 4, 0 });
        RenderTextTile("YOU FOUND BIG WHOOP", { 4, 1 });
        RenderTextTile("Press SPACEBAR to Restart", { 2, 12 });
    }
}

