#include "engine/engine.h"


void Engine::update(sf::Time dt)
{
    // Update tie fighters
    m_squadron->update(dt.asSeconds());

    m_missiles = MissileStorage::instance()->getMisiles();

    // Update the missiles
    for (uint i = 0; i < m_missiles->size(); i++)
    {
        m_missiles->at(i).update(dt.asSeconds());
    }

    m_ship->update(dt.asSeconds());


    if (m_gameTime.asSeconds() - m_lastHUDUpdate.asSeconds() >=
                                            m_hud->update_interval)
    {
        // Update the HUD
        m_hud->updateScores(m_score, m_highScore);
        m_lastHUDUpdate = m_gameTime;
    }

}

