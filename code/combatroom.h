#ifndef COMBATROOM_H
#define COMBATROOM_H

#include "room.h"
#include "player.h"
#include "enemy.h"
#include <QString>

class CombatRoom : public Room {
public:
    CombatRoom();

    QString description() const override;
    void enter(Player &player, Enemy *&enemy) override;

    // Métodos de combate
    QString playerAttack(Player &player, Enemy *&enemy);
    QString playerDefend(Player &player);
    QString playerUseItem(Player &player, const QString &item);
    QString playerFlee(Player &player);

    QString enemyAttack(Player &player, Enemy *&enemy);

    bool isPlayerTurn() const;
    void setPlayerTurn(bool turn);

    bool isPlayerDefending() const;
    void setPlayerDefending(bool def);

    bool combatOver() const;
    void setCombatOver(bool over);

private:
    bool playerTurn;
    bool playerDefending;
    bool gameOver;
};

#endif
