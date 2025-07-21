#ifndef EQUIPMENTROOM_H
#define EQUIPMENTROOM_H

#include "room.h"

class EquipmentRoom : public Room {
public:
    QString description() const override;
    void enter(Player &player, Enemy *&) override;
};

#endif