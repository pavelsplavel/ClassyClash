#include "Character.h"
#include "raymath.h"

Character::Character(int posX, int poxY)
{
    width = texture.width / maxFrames;
    height = texture.height;

    ScreenPos.x = posX/2;
    ScreenPos.y = poxY/4;
}

void Character::TakeDamage(float damage)
{ 
    health -= damage;
    if(health <= 0.f)
    {
        SetIsAlive(false);
    }
}

void Character::EventTick(float deltaTime)
{
    if(!GetIsAlive()) return;
    worldPosLastFrame = WorldPos;
    
    offset.x = 0.f;
    offset.y = 0.f;

    if( IsKeyDown(KEY_A) && CheckXMin(WorldPos)) 
    {
        velocity.x += 1;
        offset.x = -scale_offset;
    }
    if( IsKeyDown(KEY_D) && CheckXMax(WorldPos)) 
    {
        velocity.x -= 1;
        offset.x = scale_offset;
    }
    if( IsKeyDown(KEY_W) && CheckYMin(WorldPos)) 
    {
        velocity.y += 1;
        offset.y = -scale_offset;
    }
    if( IsKeyDown(KEY_S) && CheckYMax(WorldPos)) 
    {
        velocity.y -= 1;
        offset.y = scale_offset;
    }

    BaseCharacter::EventTick(deltaTime);
    
    float rotation{};
    if(GetLeftRight() > 0)
    {
        swordOrigin = {0.f, sword.height * scaleTexture};
        swordOffset = {35.f, 55.f};
        weaponCollisionRec = {
            GetScreenPos().x + swordOffset.x,
            GetScreenPos().y + swordOffset.y - sword.height * scaleTexture,
            sword.width * scaleTexture,
            sword.height * scaleTexture
        };
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = 35.f : rotation = 0.f;
    }
    else
    {
        swordOrigin = {sword.width * scaleTexture, sword.height * scaleTexture};
        swordOffset = {25.f, 55.f};
        weaponCollisionRec = {
            GetScreenPos().x + swordOffset.x - sword.width * scaleTexture,
            GetScreenPos().y + swordOffset.y - sword.height * scaleTexture,
            sword.width * scaleTexture,
            sword.height * scaleTexture
        };
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = -35.f : rotation = 0.f;
    }

    //draw sword
    //Draw Knight texture
    Rectangle swordSource{GetCurrentFrame() * width, 0.f, GetLeftRight() * width, height};
    Rectangle swordDest{GetScreenPos().x + swordOffset.x, GetScreenPos().y + swordOffset.y, scaleTexture * width, scaleTexture * height };
    weaponCollisionRec = swordDest;
    DrawTexturePro(sword, swordSource, swordDest, swordOrigin, rotation, WHITE);
    // DrawRectangleLines
    // (
    //     weaponCollisionRec.x,
    //     weaponCollisionRec.y,
    //     weaponCollisionRec.width,
    //     weaponCollisionRec.height,
    //     RED
    // );
}