#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include "Character.h"

//Global variables
Vector2 MapPos{0.0, 0.0};

class Character
{
private:
    Texture2D texture{LoadTexture("Asset/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("Asset/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("Asset/knight_run_spritesheet.png")};
    Vector2 ScreenPos{};
    Vector2 WorldPos{};
    float leftRight{-1};
    int WalkSpeed{5};
    float runningTime{};
    float updateTime= 1.0/12.0;
    int Frame{};

public:
    void EventTick(float deltaTime);
    
    //Getter
    float GetWalkSpeed() {return WalkSpeed;}
    float GetRunningTime() {return runningTime;}
    float GetUpdateTime(){return updateTime;}
    int GetCurrentFrame(){return Frame;}
    Texture2D GetTexture(){return texture;}
    float GetLeftRight(){return leftRight;}
    Vector2 GetScreenPos(){return ScreenPos;}
    Vector2 GetWorldPos(){return WorldPos;}

    //Setter
    void AddFrame(){Frame++;}
    int SetFrame(int newFrame){Frame == newFrame;}
    void SetRunningTime(float newRunningTime) {newRunningTime == 0.f ? runningTime = 0.f : runningTime += newRunningTime;}
    void SetScreenPos(int width, int height);
    void SetTexture(bool IsIdle) {IsIdle ? texture = idle : texture = run;};
    void SetLeftRight(float newLeftRight) {leftRight = newLeftRight;};
    void SetWorldPos(Vector2 newWorldPos){WorldPos = newWorldPos;}
};

void Character::SetScreenPos(int width, int height)
{
    ScreenPos.x = width;
    ScreenPos.y = height;
}

void Character::EventTick(float deltaTime)
{
    Vector2 direction{};
    if(IsKeyDown(KEY_A)) direction.x -= 1;
    if(IsKeyDown(KEY_D)) direction.x += 1;
    if(IsKeyDown(KEY_W)) direction.y -= 1;
    if(IsKeyDown(KEY_S)) direction.y += 1;
    if( Vector2Length(direction) != 0 )
    {
        SetWorldPos( Vector2Subtract(GetWorldPos(), Vector2Scale(Vector2Normalize(direction), GetWalkSpeed())) );
        direction.x < 0.0 ? SetLeftRight(-1.f) : SetLeftRight(1.f);
        SetTexture(false);
    }
    else
    {
        SetTexture(true);
    }

    //Knight idle animation
    SetRunningTime(deltaTime);
    if( GetRunningTime() >= GetUpdateTime() )
    {
        SetRunningTime(0.f);
        AddFrame();
        if(GetCurrentFrame() > 5)
        {
            SetFrame(0);
        }
    }

    //Draw Knight texture
    Rectangle source{GetCurrentFrame() * (float)GetTexture().width/6, 0.f, GetLeftRight() * (float)GetTexture().width/6, (float)GetTexture().height};
    Rectangle dest{GetScreenPos().x, GetScreenPos().y, 4.f * (float)GetTexture().width/6, 4.f * (float)GetTexture().height };
    DrawTexturePro(GetTexture(), source, dest, Vector2{}, 0.f, WHITE);
}

int main()
{
    //window
    const int windowRes{768}; //768
    InitWindow(windowRes, windowRes, "ClassyClash game");

    //WorldMap
    Texture2D MapTexture = LoadTexture("Asset/WorldMap.png");

    //Knight
    Character Knight;

    float dt{};

    Knight.SetScreenPos(windowRes/2, windowRes/4);    
    
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        //Texture WorldMap
        DrawTextureEx(MapTexture, Knight.GetWorldPos(), 0.0, 4.0, WHITE);

        //Character Knight;
        Knight.EventTick( GetFrameTime() );

        //Print String
        //float NUM = Vector2Normalize(direction);
        // std::string tmp = std::to_string(X);
        // char const *num_char = tmp.c_str();
        // DrawText(num_char, windowRes/2, windowRes/2, 40, WHITE);

        EndDrawing();
    }

    UnloadTexture(MapTexture);
    UnloadTexture(Knight.GetTexture());
    //UnloadTexture(KnightRun);
    CloseWindow();
}