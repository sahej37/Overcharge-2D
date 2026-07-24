#ifndef MAP
#define MAP_H

#include "raylib.h"
#include <vector>

class Map {
    public:
        Map(int mapSize, Vector2 mapStart);
        ~Map();  
        void Update();
        void Draw(Camera2D camera);
    
    private:
        int size;
        Vector2 pos;
        Texture2D texture;

        Texture2D brownTile;

        std::vector<std::vector<int>> grid;
};

#endif