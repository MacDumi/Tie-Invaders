#pragma once
#include <SFML/Graphics.hpp>
#include <gameobjects/missile.h>
#include <vector>
class MissileStorage
{
private:
    std::vector<Missile> m_missiles;
    static MissileStorage* m_s_Instance;
    MissileStorage();

public:
    MissileStorage (MissileStorage  const &) = delete;
    MissileStorage &operator=(MissileStorage const &) = delete;
    static MissileStorage *instance();
    void addMissile(float startX, float starY, int type);
    std::vector<Missile>* getMisiles();
};
