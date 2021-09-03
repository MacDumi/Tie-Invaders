#include "missilestorage.h"

MissileStorage* MissileStorage::m_s_Instance = nullptr;

MissileStorage::MissileStorage()
{
}

MissileStorage *MissileStorage::instance()
{
    // Returns the instance of the MissileStorage object
    if(m_s_Instance==nullptr){
        m_s_Instance = new MissileStorage();
    }
    return m_s_Instance;
}

void MissileStorage::addMissile(float startX, float startY, int type)
{
    Missile missile;
    missile.shoot(startX, startY, type);
    m_missiles.push_back(missile);
}

std::vector<Missile>* MissileStorage::getMisiles()
{
    // Remove the missiles that are not flying
    m_missiles.erase(std::remove_if(
                    m_missiles.begin(), m_missiles.end(),
                    [](Missile& x){return !x.isInFlight();}),
                    m_missiles.end());
    return &m_missiles;
}
