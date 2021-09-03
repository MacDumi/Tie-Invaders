#include "engine/engine.h"
#include <iostream>

/* Handle user input while playing */
void Engine::inputPlaying()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        if (m_gameTime.asSeconds() - m_lastPressed.asSeconds() >=
                                    m_menu->update_interval)
        {
            changeState(PAUSE);
            m_lastPressed = m_gameTime;
            SoundEngine::playSelect();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_ship->moveLeft(true);
    }
    else
    {
        m_ship->moveLeft(false);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_ship->moveRight(true);
    }
    else
    {
        m_ship->moveRight(false);
    }
    // Shoot the missile
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        m_ship->fire();
    }
}

/* Input while the game is paused */
void Engine::inputPause()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        if (m_gameTime.asSeconds() - m_lastPressed.asSeconds() >=
                                    m_menu->update_interval)
        {
            changeState(PLAYING);
            SoundEngine::playSelect();
            m_lastPressed = m_gameTime;
        }
    }
}

/* Input for the __About to quit__ dialog */
void Engine::inputAboutToQuit()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        m_window->close();
    }
}

/* Handle the input in the Menu */
void Engine::inputMenu()
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        if (m_gameTime.asSeconds() - m_lastPressed.asSeconds() >=
                                    m_menu->update_interval)
        {
            m_lastPressed = m_gameTime;
            if(m_menu->select())
            {
                m_ship_type = m_menu->getShipIdx();
                startGame();
            }
       }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (m_gameTime.asSeconds() - m_lastPressed.asSeconds() >=
                                    m_menu->update_interval)
        {
            m_lastPressed = m_gameTime;
            m_menu->input(false);
        }
    }
 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (m_gameTime.asSeconds() - m_lastPressed.asSeconds() >=
                                    m_menu->update_interval)
        {
            m_lastPressed = m_gameTime;
            m_menu->input(true);
        }
    }
}

/* Handle the input after the player lost */
void Engine::inputGameOver()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        if (m_gameTime.asSeconds() - m_lastPressed.asSeconds() >=
                                    m_menu->update_interval)
        {
            changeState(MENU);
            SoundEngine::playSelect();
            m_lastPressed = m_gameTime;
        }
    }
}

/* Inputs that work everywhere */
void Engine::inputCommon()
{

    // Quit the game?
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) &&
        m_gameTime.asSeconds() - m_lastPressed.asSeconds() >=
                                    m_menu->update_interval)
    {
        m_lastPressed = m_gameTime;
        SoundEngine::playSelect();

        switch (m_state)
        {
            case ABOUTTOQUIT: changeState(m_lastState); break;
            default: changeState(ABOUTTOQUIT);
        }
    }
    // Close event
    sf::Event event;
    while (m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window->close();
        if (event.type == sf::Event::Resized)
        {
            m_width = event.size.width;
            m_height = event.size.height;
            updateSize();
        }
    }
}
