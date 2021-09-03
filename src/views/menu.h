#pragma once
#include <SFML/Graphics.hpp>
#include "utils/bmp_storage.h"
#include "utils/assets.h"
#include "utils/soundengine.h"
#include <vector>
#include <string>
#include <iostream>

class Menu
{
    private:
        enum STATES {MENU, CONTROLS, ABOUT};
        // Current state
        STATES state = MENU;
        // Render window
        sf::RenderWindow* m_window;
        // Screen dimensions 
        int m_width, m_height;
        // Font for the text
        sf::Font m_font;
        // View
        sf::View m_view, m_credits;
        // Ship sprite
        std::vector<sf::Sprite> m_ships;
        // Index of the selected ship
        int idx = 0;
        // Different sizes
        int size_0, size_1, size_2, size_3, size_4, size_footer, padding;
        // Other options
        std::vector<std::string> options = {"Controls", "About"};

        // Get text objects
        sf::Text text(std::string string, int x, int y, int size,
                             sf::Color color = sf::Color::Yellow);
        sf::Text text(std::string string, int y, int size,
                             sf::Color color = sf::Color::Yellow);
        // Get Sprite objects
        sf::Sprite image(std::string path, int x, int y, int size,
                                bool centered=false);

        // Draw different states
        void drawMainMenu(int startY);
        void drawAbout(int startY);
        void drawControls(int startY);

    public:
        // Update interval
        const float update_interval = 0.3;
        // Constructor
        Menu(sf::RenderWindow *window, int width, int height);
        void changeSize(int width, int height);
        void drawMenu();
        void drawPause();
        void drawGameOver();
        void drawQuitMenu();
        void input(bool down);
        bool select();
        int getShipIdx();
};
