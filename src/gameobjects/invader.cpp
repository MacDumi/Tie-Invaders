#include "gameobjects/invader.h"
#include "utils/bmp_storage.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>


void Invader::spawn(float startX, float startY, int type,
                    int seed, float minX, float maxX)
{
    switch (type)
    {
    case 0:
        // Small Tie
        setTexture("assets/graphics/tie_0.png");
        break;
    case 1:
        // Large Tie
        setTexture("assets/graphics/tie_1.png");
        break;
    case 2:
        // Double Tie
        setTexture("assets/graphics/tie_2.png");
        break;
    }
    m_type = type;
    configure(startX, startY, minX, maxX, seed);
    setShootDir(1);
    srand((int)time(0) + startY + startX);
    float rand_nr = -0.5 + static_cast <float> (rand()) /
                    ( static_cast <float> (RAND_MAX/(1.5)));
    m_Position.x = m_field.width * rand_nr;

    rand_nr = (float)(rand() % 30) / 100.;
    m_Position.y = -m_field.height * (0.1 + rand_nr);

    m_animationSpeed.x = (startX - m_Position.x) / m_animationLength;
    m_animationSpeed.y = (startY - m_Position.y) / m_animationLength;
    m_starting = true;
}

uint* Invader::getDimensions()
{
    uint* size = new uint(2);
    sf::Texture texture = BmpStorage::instance()->getBmp(
                                       "assets/graphics/tie_0.png");
    size[0] = texture.getSize().x;
    size[1] = texture.getSize().y;
    return size;
}

int Invader::getType()
{
    return m_type;
}

/* Update the X coordinate */
void Invader::updateX(float elapsedTime)
{
    int speed = 0.02 * std::abs(m_Speed);
    float dX = ((rand() % speed) - 0.5 * speed) * elapsedTime;
    if (m_Position.x < m_minX)
    {
        m_Speed *= -1;
        m_Position.x = m_minX + std::abs(dX);
    }
    else if (m_Position.x > m_maxX)
    {
        m_Speed *= -1;
        m_Position.x = m_maxX - std::abs(dX);
    }
    else
    {
        m_Position.x += m_Speed * elapsedTime + dX;
    }
}
