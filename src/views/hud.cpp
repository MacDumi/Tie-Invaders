#include "hud.h"
#include <sstream>


HUD::HUD(sf::RenderWindow *window, int width, int height, int highScore)
{
    m_window = window;
    m_highScore = highScore;

    m_font.loadFromFile("assets/fonts/font.ttf");
    changeSize(width, height);
}

void HUD::changeSize(int width, int height)
{
    m_width = width;
    m_height = height;
    m_view = sf::View(sf::FloatRect(0, 0, m_width, m_height));
}
sf::Text HUD::text(std::string string, int x, int y, int size, sf::Color color)
{
    sf::Text txt;
    txt.setFont(m_font);
    txt.setCharacterSize(size);
    txt.setString(string);
    txt.setFillColor(color);
    txt.setPosition(x, y);
    return txt;
}

sf::Text HUD::textCenter(std::string string, int size, sf::Color color)
{
    sf::Text txt = text(string, 0, 0, size, color);
    sf::FloatRect textRect = txt.getLocalBounds();
    txt.setOrigin(textRect.left + textRect.width/2.0f,
                         textRect.top  + textRect.height/2.0f);
    txt.setPosition(sf::Vector2f(m_width/2.0f, m_height/2.0f));
    return txt;
}

sf::Text HUD::textUpperRight(std::string string, int size, sf::Color color)
{
    sf::Text txt = text(string, 0, 0, size, color);
    txt.setPosition(m_width - txt.getLocalBounds().width
                            - m_horPadding, m_verPadding);
    return txt;
}

sf::Text HUD::textUpperLeft(std::string string, int size, sf::Color color)
{
    sf::Text txt = text(string, 0, 0, size, color);
    txt.setPosition(m_horPadding, m_verPadding);
    return txt;
}

sf::Text HUD::textUpperCenter(std::string string, int size, sf::Color color)
{
    sf::Text txt = text(string, 0, 0, size, color);
    sf::FloatRect textRect = txt.getLocalBounds();
    txt.setOrigin(textRect.left + textRect.width/2.0f, 0);
    txt.setPosition(m_width/2.0f, m_verPadding);
    return txt;
}

void HUD::drawMessage(std::string message)
{
    m_window->setView(m_view);

    float width = m_width / 3, height = m_height / 4.5;
    sf::RectangleShape background(sf::Vector2f(width, height));
    background.setOutlineColor(sf::Color::Yellow);
    background.setOutlineThickness(2);
    background.setPosition(m_width / 2 - width / 2, m_height / 2 - height / 2);
    background.setFillColor(sf::Color(26, 26, 26, 200));
    m_window->draw(background);

    auto text = textCenter(message, m_height/30,
                                    sf::Color(255, 255, 0, 200));
    m_window->draw(text);
}

void HUD::setSprite(sf::Sprite sprite)
{
    m_ship = sprite;
    m_ship.setOrigin(0, m_ship.getLocalBounds().height);
}

void HUD::drawHUD()
{
    m_window->setView(m_view);

    std::stringstream ss;
    ss << "Score: " << m_score;
    m_window->draw(textUpperLeft(ss.str(), m_height/30,
                                                sf::Color::Yellow));
    ss.str(std::string());;
    ss << "High Score: " << m_highScore;
    m_window->draw(textUpperRight(ss.str(), m_height/30,
                                                sf::Color::Yellow));
    ss.str(std::string());;
    ss << "Wave: " << m_wave;
    m_window->draw(textUpperCenter(ss.str(), m_height/30,
                                                sf::Color(79, 164, 238)));

    // Draw the remaining lives
    float shipWidth  = m_ship.getLocalBounds().width;
    float shipHeight = m_ship.getLocalBounds().height;
    float factor = m_height / 20 / m_ship.getLocalBounds().height;
    m_ship.setScale(factor, factor);
    shipWidth  *= factor;
    shipHeight *= factor;

    for (int i = 0; i < m_livesLeft - 1; i++)
    {
        float horPos = 2 * m_horPadding + 1.5 * i * shipWidth;
        m_ship.setPosition(horPos, m_height - m_verPadding);
        m_window->draw(m_ship);
    }
}

void HUD::updateScores(int score, int highScore)
{
    m_score = score;
    m_highScore = highScore;
}

void HUD::updateWave(int wave)
{
    m_wave = wave;
}

void HUD::updateLives(int lives)
{
    m_livesLeft = lives;
}
