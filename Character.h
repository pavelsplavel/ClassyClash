#include "raylib.h"
#include "BaseCharacter.h"

#ifndef CHARACTER_H
#define CHARACTER_H

class Character : public BaseCharacter
{
public:

    Character(int posX, int poxY);
    virtual void EventTick(float deltaTime) override;
    Texture2D sword{LoadTexture("Asset/weapon_sword.png")};
    Vector2 swordOffset{};
    Vector2 swordOrigin{};
    Rectangle weaponCollisionRec{};
    float GetHealth() const {return health;}
    void TakeDamage(float damage);
private:
    float health = 100.f;
};


#endif 