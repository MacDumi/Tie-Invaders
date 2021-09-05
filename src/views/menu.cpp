#include "menu.h"

Menu::Menu(sf::RenderWindow *window, int width, int height)
{
    m_window = window;

    m_font.loadFromFile(Assets::fontPath);
    changeSize(width, height);
}

void Menu::changeSize(int width, int height)
{

    m_width = width;
    m_height = height;

    m_view = sf::View(sf::FloatRect(0, 0, m_width, m_height));
    size_0 = m_height / 4;
    size_1 = m_height / 6;
    size_2 = m_height / 10;
    size_3 = m_height / 15;
    size_4 = m_height / 25;
    size_footer = m_height / 50;
    padding = m_height / 50;
}

/* Main menu */
void Menu::drawMenu()
{
    int startY = m_height / 50 + size_0 / 2;
    m_window->setView(m_view);
    // Draw the first word
    m_window->draw(text("TIE", startY, size_0));
    // Move the start pos and draw the second word
    startY += size_0 / 2 + padding + size_1 / 2;
    m_window->draw(text("INVADERS", startY, size_1));

    m_window->draw(image(Assets::menuTieLargePath, m_width / 40,
                        m_height / 10, m_height / 4));
    m_window->draw(image(Assets::menuTieSmallPath,
                        m_width - m_width / 10 - m_height / 10,
                        m_height / 10, m_height / 10));

    // Move the pos again
    startY += size_1 / 2 + 2 * padding + size_4 / 2;

    switch(state)
    {
        case MENU: drawMainMenu(startY); break;
        case CONTROLS: drawControls(startY); break;
        case ABOUT: drawAbout(startY); break;
    }

}

/* Draw the main selection menu */
void Menu::drawMainMenu(int startY)
{
     // Draw the ship selector and other options
    m_window->draw(text("Choose your ship", startY, size_4,
                    sf::Color(0, 157, 247)));
    startY += size_4 / 2 + 2 * padding;
    int startX = m_width / 2 - 3 * size_4;
    // Draw the ships
    for (int i = 0; i < (int)Assets::shipNames.size(); i++)
    {
        int size = size_4, alpha = 100;
        if (i == idx)
        {
            alpha = 255;
            size = size_3;
            startY += 0.5 * padding;
        }
        auto img = image(Assets::shipTextures.at(i), startX - 2 * size,
                                                            startY, 1.2 * size);
        img.setColor(sf::Color(255, 255, 255, alpha));
        m_window->draw(img);
        m_window->draw(text(Assets::shipNames.at(i), startX, startY, size,
                                            sf::Color(0, 157, 247, alpha)));
        startY += size + 2 * padding;
        if (i == idx)
        {
            startY += 0.5 * padding;
        }
    }

    // Draw other options
    startY = m_height - options.size() * size_footer - 4 * padding;
    if (idx >= (int)Assets::shipNames.size()) startY -= 0.5 * size_footer;
    for (int i = 0; i < (int)options.size(); i++)
    {
        int size = size_footer;
        if (idx == (int)Assets::shipNames.size() + i)
        {
            size *= 2;
        }
        m_window->draw(text(options.at(i), startX, startY,
                                                    size, sf::Color::Yellow));
        startY += size + padding;

    }
}

/* Show the controls for the game */
void Menu::drawControls(int startY)
{
    m_window->draw(text("Control keys", startY, size_4,
                    sf::Color(0, 157, 247)));
    startY += size_4 / 2 + 3 * padding;
    int startX = m_width / 2 - 2 * size_4;
    for (int i = 0; i < (int)Assets::keyNames.size(); i++)
    {
        m_window->draw(image(Assets::keyTextures.at(i), startX - 5 * size_4,
                                                startY, 1.4 * size_4, true));

        m_window->draw(text(Assets::keyNames.at(i), startX, startY, size_4,
                                            sf::Color::Yellow));
        startY += size_4 + 2 * padding;
    }
}

/* Draw the about page */
void Menu::drawAbout(int startY)
{
    std::vector<std::pair<std::string, sf::Color>> message({
            {"Ever wondered how the", sf::Color(0, 157, 247)},
            { "Space Invaders game", sf::Color::Yellow},
            { "would have looked like in the", sf::Color(0, 147, 247)},
            { "Star Wars universe ?" , sf::Color::Yellow}});
    for(auto line : message)
    {
        float size = 0.8 * size_4;
        if (line.second == sf::Color::Yellow)
        {
            size *= 1.5;
            startY += 0.4 * size_4;
        }
        m_window->draw(text(line.first, startY, size,
                                    line.second));
        startY += size + padding;
    }


    // Draw the authors
    float imageSize = m_height / 7;
    startY = m_height - imageSize - 2 * padding;
    m_window->draw(image(Assets::macdumiProfilePath, m_width / 4,
                                                startY, imageSize));
    m_window->draw(image(Assets::adProfilePath, m_width / 1.9,
                                                startY, imageSize));
    m_window->draw(text("Code", m_width / 4 + imageSize + padding,
                        startY, size_4, sf::Color::Red));
    m_window->draw(text("Music", m_width / 1.9 + imageSize + padding,
                        startY, size_4, sf::Color::Red));
    startY += size_4 + padding;
    m_window->draw(text("Macdumi", m_width / 4 + imageSize + padding,
                        startY, 0.7 * size_4, sf::Color::Yellow));
    m_window->draw(text("Anis Djellali", m_width / 1.9 + imageSize + padding,
                        startY, 0.7 * size_4, sf::Color::Yellow));
    startY += 0.7 * size_4 + padding;
    m_window->draw(text("www.dumitruduca.com", m_width / 4 + imageSize + padding,
                        startY, 0.9 * size_footer, sf::Color::Yellow));
    m_window->draw(text("SoundCloud @anisdjellali", m_width / 1.9 + imageSize + padding,
                        startY, 0.9 * size_footer, sf::Color::Yellow));
}

/* Draw the __About to quit__ dialog */
void Menu::drawQuitMenu()
{
    int width = m_width / 2, height = m_height / 2.5;
    int startY = m_height / 2 -  height / 2;
    sf::RectangleShape background(sf::Vector2f(width, height));
    background.setOutlineColor(sf::Color::Yellow);
    background.setOutlineThickness(2);
    background.setPosition(m_width / 2 - width / 2, startY);
    background.setFillColor(sf::Color(26, 26, 26, 200));
    m_window->draw(background);

    startY += 1.5 * size_3;
    m_window->draw(text("Really quit?", startY, size_3));
    startY += 2 * size_3;
    m_window->draw(text("Quit / Cancel", startY, size_4));
    startY += size_3;
    m_window->draw(text("Enter / Escape", startY, 0.8 * size_4,
                                            sf::Color(0, 157, 247)));
}

void Menu::drawPause()
{
    int width = m_width / 2, height = m_height / 3;
    int startY = m_height / 2 -  height / 2;
    sf::RectangleShape background(sf::Vector2f(width, height));
    background.setOutlineColor(sf::Color::Yellow);
    background.setOutlineThickness(2);
    background.setPosition(m_width / 2 - width / 2, startY);
    background.setFillColor(sf::Color(26, 26, 26, 200));
    m_window->draw(background);

    startY += height / 2;
    m_window->draw(text("Pause", startY, size_2));
}

void Menu::drawGameOver()
{
    int width = m_width / 2, height = m_height / 2.5;
    int startY = m_height / 2 -  height / 2;
    sf::RectangleShape background(sf::Vector2f(width, height));
    background.setOutlineColor(sf::Color::Yellow);
    background.setOutlineThickness(2);
    background.setPosition(m_width / 2 - width / 2, startY);
    background.setFillColor(sf::Color(26, 26, 26, 200));
    m_window->draw(background);

    startY += size_2;
    m_window->draw(text("Game Over", startY, size_2));
    startY += 2 * size_3;
    m_window->draw(text("Menu / Quit", startY, size_4));
    startY += size_3;
    m_window->draw(text("Enter  /  Esc  ", startY, 0.8 * size_4,
                                            sf::Color(0, 157, 247)));
}

void Menu::input(bool down)
{
    if (state == STATES::MENU)
    {
        SoundEngine::playBeep();
        if (!down && idx > 0)
        {
            idx--;
        }
        else if (down && idx < (int)Assets::shipNames.size() +
                (int)options.size() - 1)
        {
            idx++;
        }
    }
}

bool Menu::select()
{
    // Change the state so we can display different submenues
    if (idx < (int)Assets::shipNames.size())
    {
        // If the user selected a ship then start the game
        return true;
    }
    else
    {
        // Else decide what is the next state
        if (state == STATES::MENU)
        {
            state = static_cast<STATES>(idx - Assets::shipNames.size() + 1);
        }
        else
        {
            state = STATES::MENU;
        }
        SoundEngine::playBeep();
        return false;
    }
}

sf::Sprite Menu::image(std::string path, int x, int y, int size, 
        bool centered)
{
    sf::Sprite img = sf::Sprite(BmpStorage::instance()->getBmp(path));
    sf::FloatRect imgRect = img.getLocalBounds();
    if (centered)
    {
        img.setOrigin(imgRect.left + imgRect.width/2.0f, 0);
    }
    float factor = size / imgRect.height;
    img.setScale(factor, factor);
    img.setPosition(x, y);
    return img;
}

sf::Text Menu::text(std::string string, int x, int y, int size,
                                                 sf::Color color)
{
    sf::Text txt;
    txt.setFont(m_font);
    txt.setCharacterSize(size);
    txt.setString(string);
    txt.setFillColor(color);

    txt.setPosition(x, y);
    return txt;
}

sf::Text Menu::text(std::string string, int y, int size,
                                        sf::Color color)
{
    sf::Text txt = text(string, 0, 0, size, color);

    sf::FloatRect textRect = txt.getLocalBounds();
    txt.setOrigin(textRect.left + textRect.width/2.0f,
                         textRect.top  + textRect.height/2.0f);
    txt.setPosition(sf::Vector2f(m_width/2.0f, y));
    return txt;
}

int Menu::getShipIdx()
{
    return idx;
}
