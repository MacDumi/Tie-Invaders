#include "engine/engine.h"

void Engine::drawPlaying()
{

    for (auto &invader: *m_squadron->getSprite())
    {
        m_window->draw(invader);
    }

    for (auto &missile: *m_missiles)
    {
        m_window->draw(missile.getSprite());
    }

    if (m_ship->isAlive())
        m_window->draw(m_ship->getSprite());

    m_hud->drawHUD();
}


void Engine::drawBG()
{
    m_window->clear();
    m_window->setView(gameView);
    m_window->draw(m_background);
}

void Engine::drawCommon()
{
    m_window->display();
}


