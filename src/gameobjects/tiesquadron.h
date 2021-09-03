#pragma once
#include <SFML/Graphics.hpp>
#include "gameobjects/invader.h"
#include "utils/soundengine.h"
#include "gameobjects/missile.h"
#include <string>
#include <math.h>


class TieSquadron
{
    private:
        std::vector<Invader> m_invaders;
        int m_windowWidth = 1920, m_windowHeight = 1080;
        int m_rows = 5, m_columns = 10;
        float m_fireRate = 1.5;
        float m_gameTime = 0., m_lastShot = 0.;
        bool m_shooting;
        int m_wave = 0;
        std::vector<int> m_types;

    public:
        // Constructor
        TieSquadron(int width, int height);
        // Change the size of the window
        void changeSize(int width, int height);
        // Check if the ship is alive
        bool isAlive();
        // Check for collisions
        int collisionCheck(Missile *missile);
        // Spawn a new squadron
        void spawn();
        // Change the shooting state of the squadron
        void shoot(bool shoot);
        // Get a vector of sprites to draw
        std::vector<sf::Sprite>* getSprite();
        // Update the  position of the ship
        void update(float elapsedTime);
        // Get the wave number
        int getWave();
        // Delete all the invaders
        void clear();
};
