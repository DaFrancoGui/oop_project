#include "enemy.h"
#include <QRandomGenerator>
#include <QList>

// Struct de dados dos inimigos
struct EnemyData {
    QString name;
    int baseHp;
    int baseDmg;
};

Enemy::Enemy(int hp, int dmg) : Character(hp, dmg) {}

Enemy* Enemy::generateRandomEnemy() {
    static const QList<EnemyData> enemyList = {
        {"Goblin", 25, 6},
        {"Esqueleto", 30, 8},
        {"Orc", 35, 10},
        {"Arqueiro Sombrio", 28, 9},
        {"Cavaleiro Corrompido", 40, 11},
        {"Mago das Sombras", 22, 13}
    };

    int index = QRandomGenerator::global()->bounded(enemyList.size());
    const EnemyData& chosen = enemyList[index];

    int hp = chosen.baseHp + QRandomGenerator::global()->bounded(6);
    int dmg = chosen.baseDmg + QRandomGenerator::global()->bounded(3);

    Enemy* e = new Enemy(hp, dmg);
    e->name = chosen.name;
    return e;
}
