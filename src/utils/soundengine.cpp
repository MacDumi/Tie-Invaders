#include "soundengine.h"

SoundEngine* SoundEngine::m_s_Instance = nullptr;

SoundEngine::SoundEngine()
{
    // Load the sound in to the buffers
    m_ShootBuffer.loadFromFile("assets/sounds/shoot_1.ogg");
    m_PlayerExplodeBuffer.loadFromFile("assets/sounds/playerexplode_0.ogg");
    m_InvaderExplodeBuffer.loadFromFile("assets/sounds/invaderexplode_1.ogg");
    m_InvaderFlyBuffer.loadFromFile("assets/sounds/tie.ogg");
    m_BeepBuffer.loadFromFile("assets/sounds/click.ogg");
    m_SelectBuffer.loadFromFile("assets/sounds/select.ogg");

    // Associate the sounds with the buffers
    m_ShootSound.setBuffer(m_ShootBuffer);
    m_PlayerExplodeSound.setBuffer(m_PlayerExplodeBuffer);
    m_InvaderExplodeSound.setBuffer(m_InvaderExplodeBuffer);
    m_InvaderFlySound.setBuffer(m_InvaderFlyBuffer);
    m_BeepSound.setBuffer(m_BeepBuffer);
    m_SelectSound.setBuffer(m_SelectBuffer);

    m_combatMusic.openFromFile(Assets::combatMusicPath);
    m_combatMusic.setLoop(true);
    m_menuMusic.openFromFile(Assets::menuMusicPath);
    m_menuMusic.setLoop(true);
    m_gameOverMusic.openFromFile(Assets::gameOverMusicPath);
}

SoundEngine* SoundEngine::instance()
{
    // Returns the instance of the BmpStorage object
    if(m_s_Instance==nullptr){
        m_s_Instance = new SoundEngine();
    }
    return m_s_Instance;
}
void SoundEngine::playShoot()
{
    instance()->m_ShootSound.play();
}

void SoundEngine::playPlayerExplode()
{
    instance()->m_PlayerExplodeSound.play();
}

void SoundEngine::playInvaderExplode()
{
    instance()->m_InvaderExplodeSound.play();
}

void SoundEngine::playInvaderFly()
{
    instance()->m_InvaderFlySound.play();
}

void SoundEngine::playBeep()
{
    instance()->m_BeepSound.play();
}

void SoundEngine::playSelect()
{
    instance()->m_SelectSound.play();
}

void SoundEngine::CombatMusic(bool play)
{
    if (play)
    {
        instance()->m_combatMusic.play();
    }
    else
    {
        instance()->m_combatMusic.stop();
    }
}

void SoundEngine::MenuMusic(bool play)
{
    if (play)
    {
        instance()->m_menuMusic.play();
    }
    else
    {
        instance()->m_menuMusic.stop();
    }

}

void SoundEngine::GameOverMusic(bool play)
{
    if (play)
    {
        instance()->m_gameOverMusic.play();
    }
    else
    {
        instance()->m_gameOverMusic.stop();
    }
}
