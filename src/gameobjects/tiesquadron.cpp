#include "tiesquadron.h"
#include <iostream>


TieSquadron::TieSquadron(int width, int height)
{
    m_windowWidth = width;
    m_windowHeight = height;
    m_wave = 0;
    int types[] = 
            {18, 17, 16, 16, 14, 14, 16, 16, 17, 18,
             15, 14, 14, 14, 10, 10, 14, 14, 14, 15,
             10,  8,  7,  7,  6,  6,  7,  7,  8, 10,
              7,  6,  6,  6,  5,  5,  6,  6,  6,  7,
              6,  6,  5,  5,  5,  5,  5,  5,  6,  6};
    for (int i = 0; i < m_columns * m_rows; i++)
    {
        m_types.push_back(types[i]);
    }
}


bool TieSquadron::isAlive()
{
    return (m_invaders.size() > 0);
}

void TieSquadron::shoot(bool shoot)
{
    m_shooting = shoot;
}

std::vector<sf::Sprite>* TieSquadron::getSprite()
{
    std::vector<sf::Sprite> *sprites = new std::vector<sf::Sprite>;
    for (auto &invader: m_invaders)
    {
        sprites->push_back(invader.getSprite());
    }
    return sprites;
}

void TieSquadron::update(float elapsedTime)
{
    m_gameTime += elapsedTime;

    // Remove dead ships
    m_invaders.erase(std::remove_if(
                    m_invaders.begin(), m_invaders.end(),
                    [](Invader& x){return !x.isAlive();}),
                    m_invaders.end());

    // Move the invaders
    for (auto &invader: m_invaders)
    {
        invader.update(elapsedTime);
    }

    if (m_shooting && m_invaders.size() > 0 && !m_invaders.at(0).isStarting())
    {
        srand((int)time(0));
        int inv = rand() % (m_invaders.size());
        if (m_gameTime - m_lastShot > 1. / m_fireRate)
        {
            m_invaders.at(inv).shoot();
            m_lastShot = m_gameTime;
        }
    }

}

int TieSquadron::getWave()
{
    return m_wave;
}

void TieSquadron::changeSize(int width, int height)
{
    m_windowWidth = width;
    m_windowHeight = height;

    uint *texture_size = Invader::getDimensions();
    float invader_height = (float)m_windowHeight / 3 / (m_rows * 1.5);
    float invader_width = invader_height / texture_size[0] * texture_size[1];
    float bat_width = invader_width * 3 * m_columns;
    float move_width = m_windowWidth - bat_width;

    sf::FloatRect field(0, 0, m_windowWidth, m_windowHeight);
    Invader::setFieldSize(field);

    for (int i = 0; i < (int)m_invaders.size(); i++)
    {
        m_invaders[i].setSize(invader_height);
        m_invaders[i].changeLimits(move_width);
    }
}
void TieSquadron::spawn()
{
    // 1/3 of height
    uint *texture_size = Invader::getDimensions();
    float invader_height = (float)m_windowHeight / 3 / (m_rows * 1.5);
    float invader_width = invader_height / texture_size[0] * texture_size[1];
    float bat_width = invader_width * 3 * m_columns;
    float move_width = m_windowWidth - bat_width;

    sf::FloatRect field(0, 0, m_windowWidth, m_windowHeight);
    Invader::setFieldSize(field);
    sf::Vector2f startPos;
    startPos.y = m_windowHeight / 6 - invader_height / 2; 
    startPos.x = (m_windowWidth - bat_width) / 2;

    float x, y, minX= 0.05 * m_windowWidth, maxX= 0.95 * m_windowWidth;

    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_columns; j++)
        {
            // Spawn the new invader into the field
            x = startPos.x + 1.5 * invader_width + j * (invader_width * 3);
            y = startPos.y + i * (invader_height * 1.5);
            minX = x - startPos.x;
            maxX = minX + move_width;
            Invader invader;
            invader.setSize(invader_height);
            int type = (int)floor(m_types[i*m_columns+j]/10.);
            invader.spawn(x, y, type, i * j + j, minX, maxX);
            m_invaders.push_back(invader);
        }
    }

    SoundEngine::playInvaderFly();
    m_gameTime = 0.;
    m_lastShot = 0.;
    m_shooting = true;

    // Update the types
    for (uint i = 0; i < m_types.size(); i++)
    {
        if (m_types[i] < 29)
            m_types[i]++;
    }
    m_wave++;
}

int TieSquadron::collisionCheck(Missile *missile)
{
    for (auto &invader: m_invaders)
    {
        if (missile->getPosition().intersects(invader.getPosition()))
        {
            // Stop the bullet
            missile->stop();
            // Destroy the Invader
            invader.hit();
            SoundEngine::playInvaderExplode();
            return invader.getType() + 1;
        }
    }

    return 0;
}

void TieSquadron::clear()
{
    m_invaders.clear();
    m_wave = 0;
}
