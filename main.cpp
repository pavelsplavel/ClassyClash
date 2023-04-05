#include "Character.h"
#include "Enemy.h"
#include "Prop.h"
#include "raylib.h"
#include "raymath.h"
#include <string>

int main()
{
    // window
    const int windowRes{768};
    InitWindow(windowRes, windowRes, "ClassyClash game");

    // WorldMap
    Texture2D MapTexture = LoadTexture("Asset/OpenWorldMap24x24.png");
    Texture2D RockTexture = LoadTexture("Asset/Rock.png");

    // Character knight
    Character Knight(windowRes, windowRes);

    // Character enemy
    Enemy Goblin(
        Vector2{500.f, 500.f},
        LoadTexture("Asset/goblin_run_spritesheet.png"),
        LoadTexture("Asset/goblin_idle_spritesheet.png"));

    // Character kolobok
    Enemy Kolobok(
        Vector2{1000.f, 1000.f},
        LoadTexture("Asset/slime_run_spritesheet.png"),
        LoadTexture("Asset/slime_idle_spritesheet.png"));

    Enemy *enemies[]{&Goblin, &Kolobok};
    for (auto enemy : enemies)
    {
        enemy->SetTarget(&Knight);
    }

    // Prop rock
    Prop Rock(Vector2{500.f, 500.f}, RockTexture);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Texture WorldMap
        DrawTextureEx(MapTexture, Knight.GetWorldPos(), 0.0, 4.0, WHITE);

        Knight.EventTick(GetFrameTime());

        Rock.Render(Knight.GetWorldPos(), Knight.offset);

        // Show Knight health
        if (Knight.GetIsAlive())
        {
            std::string knightHealth = "Health: ";
            knightHealth.append(std::to_string(Knight.GetHealth()), 0, 4);
            DrawText(knightHealth.c_str(), 55.f, 45.f, 40, GREEN);
        }
        else
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }

        // Check collision of knight and prop
        if (CheckCollisionRecs(Rock.GetCollisionRec(Knight.GetWorldPos()), Knight.GetCollisionRec()))
        {
            Knight.undoMovemnt();
        }

        for (auto enemy : enemies)
        {
            enemy->EventTick(GetFrameTime());
        }

        EndDrawing();
    }

    UnloadTexture(MapTexture);
    UnloadTexture(Knight.GetTextureTexture());
    UnloadTexture(Knight.GetTextureIdle());
    UnloadTexture(Knight.GetTextureRun());
    UnloadTexture(Rock.GetTexture());

    CloseWindow();
}