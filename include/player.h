#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "raymath.h"
#include <math.h>

class Player {
private:
    Vector2 position;
    float angle;
    float movementSpeed;
    Vector2 target;
    int range;
    bool isShotting;
    Vector2 shotPos;
    Vector2 shotStartPos;
    float shotAngle;
    float shotSpeed;
    float distanceFromShot;
    int level;
    int health;
    Texture2D playerTexture;

    void Move();
    void Aim();
    void Shot();

public:
    Player(float StartX, float StartY);
    ~Player();
    void Update();
    void Draw();
};

#endif