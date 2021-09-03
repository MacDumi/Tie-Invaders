#include "missile.h"
#include "utils/bmp_storage.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SFML/Graphics.hpp>

float Missile::m_height = 0.0;
float Missile::m_maxY = 0.0;
float Missile::m_minY = 0.0;

void Missile::shoot(float startX, float startY, int type)
{

    switch (type)
    {
        case 0:
        m_Sprite = sf::Sprite(BmpStorage::instance()->getBmp(
                                "assets/graphics/missile_blue.png"));
        m_Speed *= -1;
        break;
        case 1:
        m_Sprite = sf::Sprite(BmpStorage::instance()->getBmp(
                                "assets/graphics/missile_red.png"));
        break;
    }
    // Initialize the location
    m_Position.x = startX;
    m_Position.y = startY;
    // Set its origin to its center
    m_Sprite.setOrigin(m_Sprite.getLocalBounds().width/2,
                       m_Sprite.getLocalBounds().height/2);
    // Set its position
    m_Sprite.setPosition(m_Position);


    // Resize
    float factor = m_height / m_Sprite.getLocalBounds().height;
    m_Sprite.setScale(factor, factor);
    m_InFlight = true;
}
void Missile::stop()
{
    m_InFlight = false;
}

void Missile::set_height(float height)
{
    m_height = height;
}

void Missile::set_bounds(float maxY, float minY)
{
    m_minY = minY;
    m_maxY = maxY;
}

bool Missile::isInvaderMissile()
{
    if (m_Speed > 0)
        return true;

    return false;
}
bool Missile::isInFlight()
{
    return m_InFlight;
}
// Tell the calling code where the missile is in the world
sf::FloatRect Missile::getPosition()
{
    return m_Sprite.getGlobalBounds();
}
// Get a copy of the sprite to draw
sf::Sprite Missile::getSprite()
{
    return m_Sprite;
}
// Update the missile each frame
void Missile::update(float elapsedTime)
{
    m_Position.y += m_Speed * elapsedTime;
    m_Sprite.setPosition(m_Position);

    if (m_Position.y > m_maxY || m_Position.y < m_minY)
        m_InFlight = false;
}
