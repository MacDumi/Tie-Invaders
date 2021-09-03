#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
class BmpStorage
{
private:
    std::map<std::string, sf::Texture> m_Textures;
    static BmpStorage* m_s_Instance;
    BmpStorage();

public:
    BmpStorage (BmpStorage  const &) = delete;
    BmpStorage &operator=(BmpStorage const &) = delete;
    static std::vector<std::string> ship_textures;
    static BmpStorage *instance();
    sf::Texture &getBmp(std::string const& filename);
};
