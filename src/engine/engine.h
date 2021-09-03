#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "gameobjects/playableship.h"
#include "gameobjects/missile.h"
#include "gameobjects/tiesquadron.h"
#include "views/hud.h"
#include "views/menu.h"
#include "utils/missilestorage.h"
#include "utils/bmp_storage.h"
#include "utils/soundengine.h"
#include "utils/assets.h"
#include "utils/misc.h"
#include <iostream>
#include <sstream>


enum GAMESTATE {MENU, PLAYING, PAUSE, GAMEOVER, ABOUTTOQUIT};
class Engine
{
    private:
        const float COOLDOWN = 3.0;
        const int MAX_FPS = 60;
        GAMESTATE m_state = MENU, m_lastState = MENU;
        // Screen dimensions 
        int m_width, m_height;
        // Rendered window
        sf::RenderWindow *m_window;
        // Clock
        sf::Clock m_clock;
        // Time variables
        sf::Time m_lastPressed, m_gameTime, m_lastHUDUpdate,
                 m_lastDrawn, m_cooldownTime;
        // Squadron of tie fighters
        TieSquadron *m_squadron;
        // Playable ship object
        PlayableShip *m_ship;
        // Ship type index
        int m_ship_type = 0;
        // Missiles
        std::vector<Missile> *m_missiles;
        // Background Sprite
        sf::Sprite m_background;
        // Available lives Sprite
        sf::Sprite lives;
        // Scores
        int m_score = 0, m_highScore;
        // Lives left
        int m_livesLeft;
        // Different views
        sf::View gameView;
        // HUD object
        HUD* m_hud = nullptr;
        // Menu object
        Menu* m_menu = nullptr;

        // Misc functions
        void changeState(GAMESTATE state);
        void initialize(bool windowed = false);
        void updateSize();
        // High score methods
        void getHighScore();
        void updateHighScore();
        // Game stages
        void startGame();
        void levelUp();
        // Handle user input
        void inputPlaying();
        void inputMenu();
        void inputGameOver();
        void inputPause();
        void inputAboutToQuit();
        void inputCommon();
        // Handle the update for all the components
        void update(sf::Time dt);
        void updatePlaying(sf::Time dt);
        // Draw everything to the screen
        void drawPlaying();
        void drawBG();
        void drawCommon();
        // Collision detection
        void collisions();

    public:
        // Constructor
        Engine();
        Engine(int width, int height);
        // Destructor
        ~Engine();
        // Start the engine
        void run();

};
