#include "Prop.h"
#include "raymath.h"
#include "raylib.h"

Prop::Prop(Vector2 pos, Texture2D tex) : 
    WorldPos(pos), 
    Texture(tex)
{

}

void Prop::Render(Vector2 knightPos, Vector2 offset)
{
    Vector2 ScreenPos{Vector2Add(Vector2Add(knightPos, WorldPos), offset)};
    DrawTextureEx(Texture, ScreenPos, 0.f, scale, WHITE);
}

Rectangle Prop::GetCollisionRec(Vector2 knightPos)
{
    return Rectangle 
    {
        GetWorldPos().x + 10,
        GetWorldPos().y + 10,
        Texture.width * 3.f,
        Texture.height * 3.f
    };
}