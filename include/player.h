#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {
    public:
        Vector2 position;
        float speed;
        int level;
        int health;

        Player(float StartX, float StartY);

        void Update();
        void Draw();
};

#endif