#pragma once
#include <SFML/Graphics.hpp>
#include "utils/bmp_storage.h"
#include "utils/assets.h"
#include "utils/missilestorage.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

class Ship
{
    private:
        // Shooting direction: 0 - upwards, 1 - downwards
        int m_shootDirection = 0;
        sf::Sprite m_Sprite;
        float m_originalY, m_dY;
        float m_explosionTime = 0.3;
        int m_seed;

        // Change the Y position
        void updateY(float elapsedTime);
        // Display the explosion texture
        void displayExplosion(float elapsedTime);
        // Change the X position
        virtual void updateX(float elapsedTime) = 0;
        // Handle the fly-in of the ship
        void startUp(float elapsedTime);

    public:
        // Resize the ship
        void resize();
        // Change limits
        void changeLimits(int minX, int maxX);
        void changeLimits(int width);
        void changeLimits();
        // Update Y pos
        void updateYPos(int newY);
        // Set shooting direction
        void setShootDir(int direction);
        // Enable shooting
        void setShooting(bool shooting);
        // Get shooting state
        bool getShooting();
        // Set Sprite texture
        void setTexture(std::string path);
        // Handle when the ship is hit by a missile
        void hit();
        // Check if the ship is alive
        bool isAlive();
        // Check if the starting animation finished
        bool isStarting();
        // Spawn a new  ship
        virtual void spawn(float startX, float startY, int type,
                                int seed, float minX, float maxX) = 0;
        // Shoot a missile
        void shoot();
        // Get the position of the invader ship
        sf::FloatRect getPosition();
        // Get a copy of the sprite to draw
        sf::Sprite getSprite();
        // Update the  position of the ship
        void update(float elapsedTime);
        // Static function for setting the size of the ship
        void setSize(float height);
        // Static function for setting the size of the battlefield
        static void setFieldSize(sf::FloatRect field);

    protected:
        static sf::FloatRect m_field;
        float m_animationLength = 2.;
        bool m_starting = true,
             m_alive = true,
             m_hit = false,
             m_shooting = true;
        sf::Vector2f m_animationSpeed;
        float m_time = 0., m_gameTime = 0.;
        float m_minX, m_maxX;
        float m_Speed = 150;
        sf::Vector2f m_Position, m_StartPosition;
        float m_height;
        // Load different assets
        void configure(float startX, float startY,
                            float minX, float maxX, int seed=0);
};
