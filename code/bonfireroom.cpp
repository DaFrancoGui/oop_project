#include "bonfireroom.h"
#include "player.h"

QString BonfireRoom::description() const {
    return "Você descansou na fogueira. Recuperou HP.";
}

void BonfireRoom::enter(Player &player, Enemy *&) {
    player.heal();
}
