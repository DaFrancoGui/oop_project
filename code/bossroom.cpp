#include "bossroom.h"
#include "enemy.h"

QString BossRoom::description() const {
    return "Você encontrou o CHEFE FINAL!";
}

void BossRoom::enter(Player &, Enemy *&enemy) {
    enemy = new Enemy(120, 20);
    enemy->name = "Rei Lich Mortius";
}
