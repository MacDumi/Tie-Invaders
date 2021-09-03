#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "gameobjects/ship.h"
#include "utils/soundengine.h"
#include "utils/assets.h"
#include <iostream>
class PlayableShip : public Ship
{
    private:
        // Start-up animation duration (s)
        bool m_MovingRight = false;
        bool m_MovingLeft = false;
        // Type of the ship
        int m_type;
        // Max speed
        float const maxSpeed = 500;
        // Initial speed
        float const minSpeed = 300;
        // Max fire rate
        float const maxFireRate = 10;
        // Max fire rate
        float const minFireRate = 2;
        // Fire rate
        float m_fireRate;
        float m_lastShot = 0.;
        // last upgrades
        float m_speedUpgrade = 0, m_fireUpgrade = 0;
        // Change the X position
        void updateX(float elapsedTime);

    public:
        // Spawn a new ship
        void spawn(float startX, float startY, int type,
                   int seed=-1, float minX=-1, float maxX=-1);
        // Respawn the ship
        void respawn();
        // Shoot
        void fire();
        // Get the texture path
        std::string getTexturePath(int type);
        // Movement methods
        void moveLeft(bool move);
        void moveRight(bool move);
        // Modify the speed
        void resetSpeed();
        void updateSpeed(float pct);
        // Modify the fire rate
        void resetFireRate();
        void updateFireRate(float pct);
        // Get the last upgrade
        std::string getUpgrade();
};
