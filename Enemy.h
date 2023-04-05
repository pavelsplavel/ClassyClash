#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
private:
    Character* target;
    Rectangle EnemyCollision{};
    float damagePerSec{100.f};

public:
    Enemy
    (   
        Vector2 pos, 
        Texture2D idle_tex, 
        Texture2D run_tex
    );
    
    virtual void EventTick(float deltaTime) override;
    //Getter
    Vector2 newPos{};
    Vector2 oldWorldPos{};   
    //Setter
    void SetTarget(Character* character){target = character;}
    Rectangle GetEnemyCollision(){return EnemyCollision;}
    float GetDamagePerSec(){return damagePerSec;}
    float radius{30.f};
    float execVectorLen{};
    };