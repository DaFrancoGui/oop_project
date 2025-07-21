#ifndef BOSSROOM_H
#define BOSSROOM_H

#include "combatroom.h"

class BossRoom : public CombatRoom {
public:
    QString description() const override;
    void enter(Player &, Enemy *&enemy) override;
};

#endif