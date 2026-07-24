#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {
public:
    Vector2 position;
    float angle;
    float movementSpeed;
    Vector2 target;
    float range;
    
    bool isShooting;
    Vector2 shotPos;
    Vector2 shotStartPos;
    Vector2 shotDir; 
    float shotSpeed;
    
    int level;
    int health;
    Texture2D playerTexture;

    Player(float StartX, float StartY);
    ~Player();

    void Move();
    void Aim(Camera2D camera);
    void Shot();
    void Update(Camera2D &camera);
    void Draw();
};

#endif