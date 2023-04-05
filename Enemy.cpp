#include "BaseCharacter.h"
#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex)
{
    WorldPos = pos;
    texture = idle_tex;
    idle = idle_tex;
    run = run_tex;

    width = texture.width / maxFrames;
    height = texture.height;
}

void Enemy::EventTick(float deltaTime)
{
    if(!GetIsAlive()) return;
    worldPosLastFrame = WorldPos;
    oldWorldPos = GetWorldPos();

    //Chasing character
    velocity = Vector2Subtract(target->GetWorldPosReal(), GetWorldPos());
    execVectorLen = Vector2Length(velocity);
    velocity = Vector2Normalize(velocity);
    velocity = Vector2Scale(velocity, 3.5f);
    velocity = Vector2Add(velocity, GetWorldPos());

    if( !(execVectorLen <= radius) ) 
    {
        SetWorldPos(velocity);
        SetTexture(true);
    }
    else
    {
        SetTexture(false);
    }

    //PrintNumToString(execVectorLen, true, 500);

    //Check if enemy and sword coliding and sword attack
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionRecs(GetEnemyCollision(), target->weaponCollisionRec))
    {
        SetIsAlive(false);
    }

    //Check if enemy colliding knight
    if( CheckCollisionRecs(target->CharacterRec, GetEnemyCollision()) && GetIsAlive() )
    {
        target->TakeDamage(GetDamagePerSec() * GetFrameTime());
    }

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

    //Update position
    newPos = Vector2Add(WorldPos, target->GetWorldPos());
    SetScreenPos(newPos);
    
    float execSide = target->GetWorldPosReal().x - GetWorldPos().x;
    if(execSide > 0)
    {
        SetLeftRight(1.f);
    }
    else
    {
        SetLeftRight(-1.f);
    }

    //Draw Knight texture
    Rectangle source{GetCurrentFrame() * width, 0.f, GetLeftRight() * width, height};
    Rectangle dest{GetScreenPos().x, GetScreenPos().y, scaleTexture * width, scaleTexture * height };
    EnemyCollision = dest;
    DrawTexturePro(GetTextureTexture(), source, dest, Vector2{}, 0.f, WHITE);
}
