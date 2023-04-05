#include "raylib.h"

class Prop
{
private:
    Texture2D Texture{};
    Vector2 WorldPos{};
    Vector2 ScreenPos;
    float scale{4.f};

public:
    Prop(Vector2 pos, Texture2D tex);
    void Render(Vector2 knightPos, Vector2 offset);
    void CheckCollision(Vector2 knightPos);

    //Getter
    Texture2D GetTexture(){return Texture;}
    Rectangle GetCollisionRec(Vector2 knightPos);
    Vector2 GetWorldPos(){return WorldPos;}
    Vector2 GetScreenPos(){return ScreenPos;}
};