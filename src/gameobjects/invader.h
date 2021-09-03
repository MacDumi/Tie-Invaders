#pragma once
#include <SFML/Graphics.hpp>
#include "gameobjects/ship.h"

class Invader : public Ship
{
    private:
        // Change the X position
        void updateX(float elapsedTime);
        int m_type;

    public:
        // Spawn a new invader
        void spawn(float startX, float startY, int type,
                                int seed, float minX, float maxX);
        // Get the dimension of the texture
        static uint* getDimensions();
        // Get the type
        int getType();
};
