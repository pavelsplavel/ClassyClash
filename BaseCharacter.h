#include "raylib.h"

#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

class BaseCharacter
{
public:
    BaseCharacter();

    virtual void EventTick(float deltaTime);
    
    Vector2 offset{0.f, 0.f};
    Vector2 worldPosLastFrame{};
    float scale_offset{4.5f};
    Vector2 velocity{};
    Rectangle CharacterRec {};

    void undoMovemnt();
    //Gettter
    Texture2D GetTextureTexture(){return texture;}
    Texture2D GetTextureIdle(){return idle;}
    Texture2D GetTextureRun(){return run;}
    float GetWalkSpeed(){return WalkSpeed;}
    float GetRunningTime(){return runningTime;}
    float GetUpdateTime(){return updateTime;}
    int GetCurrentFrame(){return Frame;}
    float GetLeftRight(){return leftRight;}
    Vector2 GetScreenPos(){return ScreenPos;}
    Vector2 GetWorldPos();
    Vector2 GetWorldPosReal();
    bool GetIsRun(){return IsRun;}
    Rectangle GetCollisionRec();
    bool GetIsAlive(){return isAlive;}

    //Setter
    void SetTexture(bool IsIdle) {IsIdle ? texture = idle : texture = run;};
    void SetFrame(int newFrame){Frame = newFrame;}
    void SetRunningTime(float newRunningTime) {newRunningTime == 0.f ? runningTime = 0.f : runningTime += newRunningTime;}
    void SetLeftRight(float newLeftRight) {leftRight = newLeftRight;};
    void SetWorldPos(Vector2 newWorldPos){WorldPos = newWorldPos;}
    void SetIsRun(bool isRun){ IsRun = isRun;}
    void PrintNumToString(float valuePrint, bool color, int yPosPrintText);
    void AddFrame(){Frame++;}
    void SetScreenPos(Vector2 newScreenPos){ScreenPos = newScreenPos;}
    //Check map bounds
    bool CheckXMin(Vector2 position);
    bool CheckXMax(Vector2 WorldPos);
    bool CheckYMin(Vector2 WorldPos);
    bool CheckYMax(Vector2 WorldPos);
    void SetIsAlive(bool newIsAlive){isAlive = newIsAlive;}

protected:
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
    float width{};
    float height{};
    float scaleTexture{4.0};
    bool IsRun = false;
    int maxFrames{6};

private:
    bool isAlive{true};
};

#endif 