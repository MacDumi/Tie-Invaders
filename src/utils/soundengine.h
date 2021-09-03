#pragma once

#include <SFML/Audio.hpp>
#include "utils/assets.h"

class SoundEngine
{
private:
    sf::SoundBuffer m_ShootBuffer;
    sf::SoundBuffer m_PlayerExplodeBuffer;
    sf::SoundBuffer m_InvaderExplodeBuffer;
    sf::SoundBuffer m_InvaderFlyBuffer;
    sf::SoundBuffer m_BeepBuffer;
    sf::SoundBuffer m_SelectBuffer;

    sf::Sound m_ShootSound;
    sf::Sound m_PlayerExplodeSound;
    sf::Sound m_InvaderExplodeSound;
    sf::Sound m_InvaderFlySound;
    sf::Sound m_BeepSound;
    sf::Sound m_SelectSound;
    sf::Music m_menuMusic;
    sf::Music m_combatMusic;
    sf::Music m_gameOverMusic;
    static SoundEngine* m_s_Instance;
    SoundEngine();

public:
    SoundEngine (SoundEngine  const &) = delete;
    SoundEngine &operator=(SoundEngine const &) = delete;
    static SoundEngine *instance();
    static void playShoot();
    static void playPlayerExplode();
    static void playInvaderExplode();
    static void playInvaderFly();
    static void playBeep();
    static void playSelect();
    static void CombatMusic(bool play=true);
    static void MenuMusic(bool play=true);
    static void GameOverMusic(bool play=true);

};

