#ifndef ROOMFACTORY_H
#define ROOMFACTORY_H

#include "room.h"
#include <memory>

class GameWindow;

class RoomFactory {
public:
    static std::unique_ptr<Room> createRoom(int roomCount, GameWindow* window);
};

#endif
