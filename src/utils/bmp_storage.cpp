#include "bmp_storage.h"
#include <iostream>
#include <assert.h>
#define debuggingOnConsole


BmpStorage* BmpStorage::m_s_Instance = nullptr;

BmpStorage::BmpStorage()
{
}

BmpStorage *BmpStorage::instance()
{
    // Returns the instance of the BmpStorage object
    if(m_s_Instance==nullptr){
        m_s_Instance = new BmpStorage();
    }
    return m_s_Instance;
}

sf::Texture& BmpStorage::getBmp(std::string const& filename)
{
    // Get a reference to m_Textures using m_S_Instance
    auto& m = m_s_Instance->m_Textures;
    auto keyValuePair = m.find(filename);

    // Did we find a match?
    if (keyValuePair != m.end())
    {
        return keyValuePair->second;
    }
    else
    {
#ifdef debuggingOnConsole
        std::cout <<  "BmpStorage::getBitmap() Texture not found: ";
        std::cout << filename << std::endl;
#endif
        auto& texture = m[filename];
        // Load the texture from file in the usual way
        texture.loadFromFile(filename);
        // Return the texture to the calling code
        return texture;
    }
}
