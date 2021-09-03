#include "ship.h"

sf::FloatRect Ship::m_field = sf::FloatRect(0, 0, 0, 0);

void Ship::configure(float startX, float startY,
                    float minX, float maxX, int seed)
{

    // Initialize ship location
    m_Position.x = startX;
    m_Position.y = startY;
    m_StartPosition.x = startX;
    m_StartPosition.y = startY;
    // Set its position
    m_Sprite.setPosition(m_Position);
    m_originalY = startY;
    m_dY = m_height / 2;
    if (minX == -1)
        m_minX = 0.05 * m_field.left;
    else
        m_minX = minX;

    if (maxX == -1)
        m_maxX = 0.95 * (m_field.left + m_field.width);
    else
        m_maxX = maxX;
    m_seed = seed;
    m_alive = true;
    m_hit = false;

    // Resize the sprite
    resize();
}

void Ship::updateYPos(int newY)
{
    m_Position.y = newY;
    m_StartPosition.y = newY;
    m_originalY = newY;
}

void Ship::changeLimits(int minX, int maxX)
{
    m_minX = minX;
    m_maxX = maxX;
}

void Ship::changeLimits(int width)
{
    m_maxX = m_minX + width;
}

void Ship::changeLimits()
{
    m_minX = 0.05 * m_field.left;
    m_maxX = 0.95 * (m_field.left + m_field.width);
}
/* Resize the ship */
void Ship::resize()
{
    float factor = m_height / m_Sprite.getLocalBounds().height;
    m_Sprite.setScale(factor, factor);
}

/* Set the texture of the sprite */
void Ship::setTexture(std::string path)
{
    m_Sprite = sf::Sprite(BmpStorage::instance()->getBmp(path));
    // Set its origin to its center
    m_Sprite.setOrigin(m_Sprite.getLocalBounds().width/2,
                       m_Sprite.getLocalBounds().height/2);
    m_Sprite.setPosition(m_Position);
}

/* The ship was hit by a missile */
void Ship::hit()
{
    if (!m_hit)
    {
        // Change the texture to an explosion
        m_Sprite = sf::Sprite(BmpStorage::instance()->getBmp(
                                        Assets::explosionPath));
        // Set its origin to its center
        m_Sprite.setOrigin(m_Sprite.getLocalBounds().width/2,
                                  m_Sprite.getLocalBounds().height/2);
        // Resize
        float factor = m_height / m_Sprite.getLocalBounds().height;
        m_Sprite.setScale(factor, factor);
        m_hit = true;
    }
}

/* Check if the ship is still alive */
bool Ship::isAlive()
{
    return m_alive;
}

/* Check if the starting animation finished */
bool Ship::isStarting()
{
    return m_starting;
}
/* Get the position of the ship (for collision detection) */
sf::FloatRect Ship::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

/* Set the height of the ship */
void Ship::setSize(float height)
{
    m_height = height;
}

/* Set the battlefield size */
void Ship::setFieldSize(sf::FloatRect field)
{
    m_field = field;
}

/* Returns the Sprite of the ship for drawing */
sf::Sprite Ship::getSprite()
{
    return m_Sprite;
}

/* Set shooting direction */
void Ship::setShootDir(int direction)
{
    m_shootDirection = direction;
}

/* Shoot a missile */
void Ship::shoot()
{
    if (m_alive && !m_starting && m_shooting)
    {
        MissileStorage::instance()->addMissile(m_Position.x,
                                m_Position.y, m_shootDirection);
    }
}

/* Handle the explosion of the ship */
void Ship::displayExplosion(float elapsedTime)
{
    if (m_hit)
    {
        float factor = m_height / m_Sprite.getLocalBounds().height;
        factor *= 0.5 + static_cast <float> (rand()) /
                                (static_cast <float> (RAND_MAX/0.5));
        m_Sprite.setScale(factor, factor);
        m_time += elapsedTime;
        if (m_time > m_explosionTime)
        {
            m_alive = false;
            m_StartPosition.x = m_Position.x;
            m_time = 0;
        }
    }
}

/* Start-up animation */
void Ship::startUp(float elapsedTime)
{
    m_Position.y += m_animationSpeed.y * elapsedTime;
    m_Position.x += m_animationSpeed.x * elapsedTime;
    m_time += elapsedTime;
    if (m_time >= m_animationLength)
    {
        m_starting = false;
        m_shooting = true;
        m_Position = m_StartPosition;
        m_time = 0;
    }
}

/* Update the Y coordinate */
void Ship::updateY(float elapsedTime)
{
    if (m_starting)
        return
    srand((int)time(0) + m_seed);
    int speed = 0.06 * std::abs(m_Speed);
    float dY = ((rand() % speed) - 0.5 * speed) * elapsedTime; 

    if (m_Position.y + dY > m_originalY + m_dY)
    {
        m_Position.y -= std::abs(dY);
    }
    else if (m_Position.y + dY < m_originalY - m_dY)
    {
        m_Position.y += std::abs(dY);
    }
    else
        m_Position.y += dY;
}
void Ship::update(float elapsedTime)
{
    // Update the position  of the ship

    if (m_starting)
    {
        startUp(elapsedTime);
    }
    else
    {
        updateY(elapsedTime);
        updateX(elapsedTime);
        displayExplosion(elapsedTime);
    }

    m_gameTime += elapsedTime;
    // Move the sprite
    m_Sprite.setPosition(m_Position);

}

void Ship::setShooting(bool shoot)
{
    m_shooting = shoot;
}

bool Ship::getShooting()
{
    return m_shooting && !m_starting;
}
