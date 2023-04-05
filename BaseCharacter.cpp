#include "BaseCharacter.h"
#include <iostream>
#include "raylib.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{
    
}

void BaseCharacter::EventTick(float deltaTime)
{
    //Knight idle animation
    SetRunningTime(deltaTime);
    if( GetRunningTime() >= GetUpdateTime() )
    {
        SetRunningTime(0.f);
        AddFrame();
        if(GetCurrentFrame() > maxFrames)
        {
            SetFrame(0);
        }
    }

    if( Vector2Length(velocity) != 0 )
    {
        SetWorldPos( Vector2Add(GetWorldPos(), Vector2Scale(Vector2Normalize(velocity), GetWalkSpeed()) ) );
        velocity.x < 0.f ? SetLeftRight(1.f) : SetLeftRight(-1.f);
        SetTexture(false);
        SetIsRun(true);
    }
    else
    {
        SetIsRun(false);
        SetTexture(true);
    }
    velocity = {};

    //Draw Knight texture
    Rectangle source{GetCurrentFrame() * width, 0.f, GetLeftRight() * width, height};
    Rectangle dest{GetScreenPos().x, GetScreenPos().y, scaleTexture * width, scaleTexture * height };
    CharacterRec = dest;
    DrawTexturePro(GetTextureTexture(), source, dest, Vector2{}, 0.f, WHITE);
}

void BaseCharacter::undoMovemnt()
{
    WorldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec()
{
    return Rectangle
    {
        GetWorldPosReal().x,
        GetWorldPosReal().y,
        width * scaleTexture,
        height * scaleTexture
    };
}

Vector2 BaseCharacter::GetWorldPosReal()
{
    Vector2 newWorldPos;
    newWorldPos.x = 0.f;
    newWorldPos.y = 0.f;
    newWorldPos.x = -(WorldPos.x - 384.f);
    newWorldPos.y = -(WorldPos.y - 192.f);
    return newWorldPos;
}

Vector2 BaseCharacter::GetWorldPos()
{
    return WorldPos;
}

void BaseCharacter::PrintNumToString(float valuePrint, bool color, int yPosPrintText)
{
    //Print String
    //float NUM = Vector2Normalize(direction);
    // std::string tmp = std::to_string(X);
    // char const *num_char = tmp.c_str();
    // DrawText(num_char, windowRes/2, windowRes/2, 40, WHITE);

    std::string tmp = std::to_string(valuePrint);
    char const *num_char = tmp.c_str();
    if(color)
    {
        DrawText(num_char, 768/2, yPosPrintText, 40, WHITE);
    }
    else
    {
        DrawText(num_char, 768/2, yPosPrintText, 40, RED);
    }
    
}
//Check map bounds
bool BaseCharacter::CheckXMin(Vector2 position)
{
    //position.x <= 0.f ? true : false;
    if(position.x < -4)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool BaseCharacter::CheckXMax(Vector2 position)
{
    //position.x <= 0.f ? true : false;
    if(position.x > -2280.f)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool BaseCharacter::CheckYMin(Vector2 position)
{
    //position.x <= 0.f ? true : false;
    if(position.y < -30)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool BaseCharacter::CheckYMax(Vector2 position)
{
    //position.x <= 0.f ? true : false;
    if(position.y > -2280.f)
    {
        return true;
    }
    else
    {
        return false;
    }
}