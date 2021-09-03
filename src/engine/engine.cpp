#include "engine/engine.h"

Engine::Engine()
{
    // Get the screen size
    getScreenResolution(m_width, m_height);
    initialize();
}

Engine::Engine(int width, int height)
{
    // Use the provided size
    m_width = width;
    m_height = height;
    initialize(true);
}


void Engine::initialize(bool windowed)
{
    changeState(MENU);
    getHighScore();
    // Create a renderable window
    auto winStyle = 0;
    if (windowed) winStyle = sf::Style::Resize;
    m_window = new sf::RenderWindow(sf::VideoMode(m_width,
                                        m_height), "Tie Invaders", winStyle);

    m_hud  = new HUD(m_window, m_width, m_height, m_highScore);
    m_menu = new Menu(m_window, m_width, m_height);
    m_squadron = new TieSquadron(m_width, m_height);

    m_ship = new PlayableShip();

    // Deal with the background
    m_background = sf::Sprite(BmpStorage::instance()->getBmp(Assets::bgPath));
    m_background.setPosition(0,0);

    updateSize();
}

void Engine::updateSize()
{

    gameView = sf::View(sf::FloatRect(0, 0, m_width, m_height));
    m_hud->changeSize(m_width, m_height);
    m_menu->changeSize(m_width, m_height);
    m_squadron->changeSize(m_width, m_height);
    m_ship->setSize(m_height / 10);
    m_ship->changeLimits();
    m_ship->updateYPos(m_height * 0.85);

    PlayableShip::setFieldSize(sf::FloatRect(0, 0, m_width, m_height));

    Missile::set_height(m_height / 30);
    Missile::set_bounds(m_height);

    // Scale the background
    float factor_x = m_width / m_background.getLocalBounds().width;
    float factor_y = m_height / m_background.getLocalBounds().height;
    m_background.setScale(factor_x, factor_y);
}



void Engine::run()
{
    m_lastHUDUpdate = m_clock.restart();
    m_lastPressed = m_lastHUDUpdate;
    m_cooldownTime = sf::Time();
    // Run the engine while the window is open
    while (m_window->isOpen())
    {
        sf::Time dt = m_clock.restart();

        // update and input
        switch (m_state)
        {
            case MENU:
                          inputMenu();
                          break;

            case PLAYING:
                          update(dt);
                          collisions();
                          inputPlaying();
                          break;

            case PAUSE:
                         inputPause();
                         break;

            case GAMEOVER:
                         update(dt);
                         inputGameOver();
                         break;
            case ABOUTTOQUIT:
                         inputAboutToQuit();
                         break;
        }
        // Comon input
        inputCommon();

        // Limit the number of frames to MAX_FPS
        if (m_gameTime.asSeconds() - m_lastDrawn.asSeconds() >=
                                    1.0 / MAX_FPS)
        {
            // Draw the background
            drawBG();
            // Draw the elements specific for each game state
            switch (m_state)
            {
                case MENU:
                              m_menu->drawMenu();
                              break;

                case PLAYING:
                              drawPlaying();
                              break;

                case PAUSE:
                             drawPlaying();
                             m_menu->drawPause();
                             break;

                case GAMEOVER:
                             drawPlaying();
                             m_menu->drawGameOver();
                             break;
                case ABOUTTOQUIT:
                             if (m_lastState == GAMESTATE::PLAYING)
                                 drawPlaying();
                             m_menu->drawQuitMenu();
                             break;
            }

            // Draw the commoin elements
            drawCommon();
            m_lastDrawn = m_gameTime;
        }


        m_gameTime += dt;
    }

}

Engine::~Engine()
{
    // Delete all the pointers
    m_window = nullptr;
    m_squadron = nullptr;
    m_ship = nullptr;
    updateHighScore();
}
