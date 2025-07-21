#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"
#include <QString>

class Enemy : public Character {
public:
    Enemy(int hp, int dmg);

    static Enemy* generateRandomEnemy();

    QString name;  // Nome do inimigo para exibição
};

#endif
