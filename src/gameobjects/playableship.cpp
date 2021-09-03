#include "gameobjects/playableship.h"
#include "utils/bmp_storage.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <SFML/Graphics.hpp>


void PlayableShip::spawn(float startX, float startY, int type,
                    int seed, float minX, float maxX)
{
    setTexture(getTexturePath(type));
    configure(startX, startY, minX, maxX, seed);
    setShootDir(0);
    m_animationLength = 1.;
    m_animationSpeed.y = -0.2 * m_field.height / m_animationLength;
    m_animationSpeed.x = 0.0;
    m_Position.y = startY + 0.2 * m_field.height;
    m_starting = true;
    m_type = type;
}

void PlayableShip::respawn()
{
    setTexture(getTexturePath(m_type));
    m_Position.y = m_StartPosition.y + 0.2 * m_field.height;
    m_alive = true;
    m_hit = false;
    m_starting = true;
    resize();
}

/* Get the texture path for a given type */
std::string PlayableShip::getTexturePath(int type)
{
    if (type < 0 || type >= (int)Assets::shipTextures.size())
    {
        type = 0;
    }
    return Assets::shipTextures.at(type);
}

/* Reset the speed to default value */
void PlayableShip::resetSpeed()
{
    m_Speed = minSpeed;
}

/* Reset the fire rate to default value */
void PlayableShip::resetFireRate()
{
    m_fireRate = minFireRate;
}

/* Modify the speed of the ship */
void PlayableShip::updateSpeed(float pct)
{
    m_Speed += m_Speed * pct / 100;
    m_speedUpgrade = pct;
    if (m_Speed > maxSpeed)
    {
       m_Speed = maxSpeed;
       m_speedUpgrade = -1;
    }
}

/* Modify the fire rate */
void PlayableShip::updateFireRate(float pct)
{
    m_fireRate += m_fireRate * pct / 100;
    m_fireUpgrade = pct;
    if (m_fireRate > maxFireRate)
    {
        m_fireRate = maxFireRate;
        m_fireUpgrade = -1;
    }
}

/* Get the last upgrade */
std::string PlayableShip::getUpgrade()
{
    std::stringstream ss;
    ss << "Speed: ";
    if (m_speedUpgrade != -1)
        ss << "+" << m_speedUpgrade << "%";
    else
        ss << "MAX";

    ss << "\nFire Rate: ";
    if (m_fireUpgrade != -1)
        ss << "+" << m_fireUpgrade << "%";
    else
        ss << "MAX";

    return ss.str();
}

/* Fire a missile */
void PlayableShip::fire()
{
    if (getShooting() && m_gameTime - m_lastShot > 1.0 / m_fireRate)
    {
        shoot();
        SoundEngine::playShoot();
        m_lastShot = m_gameTime;
    }
}

/* Move the ship to the left */
void PlayableShip::moveLeft(bool move)
{
    m_MovingLeft = move;
}

/* Move the ship to the right */
void PlayableShip::moveRight(bool move)
{
    m_MovingRight = move;
}

void PlayableShip::updateX(float elapsedTime)
{
    // Update the x position
    if (m_MovingLeft && m_Position.x > m_minX)
    {
        m_Position.x -= m_Speed * elapsedTime;
    }

    if (m_MovingRight && m_Position.x < m_maxX)
    {
        m_Position.x += m_Speed * elapsedTime;
    }
}

