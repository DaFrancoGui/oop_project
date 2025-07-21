#ifndef BONFIREROOM_H
#define BONFIREROOM_H

#include "room.h"

class BonfireRoom : public Room {
public:
    QString description() const override;
    void enter(Player &player, Enemy *&) override;
};

#endif