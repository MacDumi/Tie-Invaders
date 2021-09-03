#pragma once
#include <SFML/Graphics.hpp>

class Missile
{
    private:
        // Where is the bullet?
        sf::Vector2f m_Position;
        sf::Sprite m_Sprite;
        bool m_InFlight = false;
        float m_Speed = 1000;
        static float m_height;
        // What fraction of 1 pixel does the bullet travel,
        // Horizontally and vertically each frame?
        // These values will be derived from m_BulletSpeed
        float m_DistanceX;
        float m_DistanceY;
        // Boundaries
        static float m_maxY;
        static float m_minY;
    public:
        void shoot(float startX, float startY, int type);
        void stop();
        static void set_height(float height);
        static void set_bounds(float maxY, float minY=0);
        bool isInFlight();
        bool isInvaderMissile();
        // Tell the calling code where the missile is in the world
        sf::FloatRect getPosition();
        // Get a copy of the sprite to draw
        sf::Sprite getSprite();
        // Update the missile each frame
        void update(float elapsedTime);
};
