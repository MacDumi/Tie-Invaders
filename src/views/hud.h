#pragma once
#include <SFML/Graphics.hpp>

class HUD
{
    private:
        // Render window
        sf::RenderWindow* m_window;
        // Screen dimensions 
        int m_width, m_height;
        // Scores
        int m_score, m_highScore;
        // Lives left
        int m_livesLeft=0;
        // Wave number
        int m_wave = 1;
        // Font for the text
        sf::Font m_font;
        // View
        sf::View m_view;
        // Text padding
        int m_horPadding = 25, m_verPadding = 10;
        // Ship sprite
        sf::Sprite m_ship;

        // Get text objects
        sf::Text text(std::string string, int x, int y, int size,
                            sf::Color color = sf::Color::Yellow);
        sf::Text textCenter(std::string string, int size,
                            sf::Color color = sf::Color::Yellow);
        sf::Text textUpperRight(std::string string, int size,
                            sf::Color color = sf::Color::Yellow);
        sf::Text textUpperLeft(std::string string, int size,
                            sf::Color color = sf::Color::Yellow);
        sf::Text textUpperCenter(std::string string, int size,
                            sf::Color color = sf::Color::Yellow);

    public:
        // Update interval
        const float update_interval = 0.3;
        // Constructor
        HUD(sf::RenderWindow *window, int width, int height, int highScore);
        void changeSize(int width, int height);
        void drawHUD();
        void setSprite(sf::Sprite sprite);
        void updateScores(int score, int highScore);
        void updateWave(int wave);
        void drawMessage(std::string message);
        void updateLives(int lives);
};
