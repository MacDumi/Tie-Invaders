#include "engine/engine.h"
#include <fstream>

void Engine::getHighScore()
{
    std::ifstream saveFile (Assets::saveScorePath);
    if (saveFile.is_open())
    {
        std::string line;
        getline (saveFile,line);
        m_highScore = atoi(line.c_str());
        saveFile.close();
    }
    else
    {
        m_highScore = 0;
    }
}

void Engine::updateHighScore()
{
    // Update the high score file
    std::ofstream saveFile(Assets::saveScorePath);
    if (saveFile.is_open())
      {
        saveFile << m_highScore << std::endl;
        saveFile.close();
      }
}

/* Start a new game */
void Engine::startGame()
{
    changeState(PLAYING);
    m_squadron->clear();
    m_squadron->spawn();
    m_ship->spawn(m_width / 2, m_height * 0.85, m_ship_type);
    m_score = 0;
    m_ship->resetSpeed();
    m_ship->resetFireRate();

    m_livesLeft = 3;
    m_hud->setSprite(m_ship->getSprite());
    m_hud->updateLives(m_livesLeft);
    m_hud->updateWave(m_squadron->getWave());
    m_clock.restart();
}

/* Change the state fo the game */
void Engine::changeState(GAMESTATE state)
{
    m_lastState = m_state;
    m_state = state;
    switch(m_state)
    {
        case MENU: 
            {
                SoundEngine::CombatMusic(false);
                SoundEngine::GameOverMusic(false);
                SoundEngine::MenuMusic();
                break;
            }
        case PLAYING:
            {
                SoundEngine::CombatMusic();
                SoundEngine::GameOverMusic(false);
                SoundEngine::MenuMusic(false);
                break;
            }
        case GAMEOVER:
            {
                SoundEngine::CombatMusic(false);
                SoundEngine::GameOverMusic();
                SoundEngine::MenuMusic(false);
                break;
            }
        default: break;
    }
}

/* Check for collisions */
void Engine::collisions()
{
    // Check for missile collisions
    for (uint i = 0; i < m_missiles->size(); i++)
    {
        if(!m_missiles->at(i).isInvaderMissile())
        {
            m_score += m_squadron->collisionCheck(&m_missiles->at(i));
            if (m_score > m_highScore)
            {
                m_highScore = m_score;
            }
        }
        else if (m_missiles->at(i).getPosition().
                intersects(m_ship->getPosition())
                && !m_ship->isStarting() && m_ship->isAlive())
        {
            m_missiles->at(i).stop();
            SoundEngine::playPlayerExplode();
            m_ship->hit();
            m_squadron->shoot(false);
            m_livesLeft--;
            m_hud->updateLives(m_livesLeft);
            m_cooldownTime = m_gameTime;
            if (m_livesLeft == 0)
            {
                changeState(GAMEOVER);
                return;
            }
        }
    }

    // If the ship is not alive wait a little before spawning a new one
    if (!m_ship->isAlive() &&
        m_gameTime.asSeconds() - m_cooldownTime.asSeconds() >= COOLDOWN)
    {
        m_ship->respawn();
        m_cooldownTime = sf::Time();
    }

    m_squadron->shoot(!m_ship->isStarting() && m_ship->isAlive());

    if (!m_squadron->isAlive())
    {
        levelUp();
    }
}

void Engine::levelUp()
{
    if( m_cooldownTime.asSeconds() == 0)
    {
        // The squadron was just destroyed
        m_cooldownTime = m_gameTime;
        m_ship->setShooting(false);
        m_ship->updateSpeed(5);
        m_ship->updateFireRate(20);
    }
    else if (m_gameTime.asSeconds() -
             m_cooldownTime.asSeconds() >= COOLDOWN)
    {
        m_squadron->spawn();
        m_ship->setShooting(true);
        m_hud->updateWave(m_squadron->getWave());
        m_cooldownTime = sf::Time();
    }
    m_hud->drawMessage(m_ship->getUpgrade());
}
