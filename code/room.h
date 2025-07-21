#ifndef ROOM_H
#define ROOM_H

#include <QString>
class Player;
class Enemy;

class Room {
public:
    virtual QString description() const = 0;
    virtual void enter(Player &player, Enemy *&enemy) = 0;
    virtual ~Room() {}
};

#endif