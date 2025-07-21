#include "combatroom.h"
#include "enemy.h"
#include <QRandomGenerator>

CombatRoom::CombatRoom()
    : playerTurn(true), playerDefending(false), gameOver(false)
{}

QString CombatRoom::description() const {
    return "Você encontrou um inimigo!";
}

void CombatRoom::enter(Player &player, Enemy *&enemy) {
    enemy = Enemy::generateRandomEnemy();

    playerTurn = true;
    playerDefending = false;
    gameOver = false;
}

bool CombatRoom::isPlayerTurn() const {
    return playerTurn;
}

void CombatRoom::setPlayerTurn(bool turn) {
    playerTurn = turn;
}

bool CombatRoom::isPlayerDefending() const {
    return playerDefending;
}

void CombatRoom::setPlayerDefending(bool def) {
    playerDefending = def;
}

bool CombatRoom::combatOver() const {
    return gameOver;
}

void CombatRoom::setCombatOver(bool over) {
    gameOver = over;
}

QString CombatRoom::playerAttack(Player &player, Enemy *&enemy) {
    if (!playerTurn || gameOver || enemy == nullptr)
        return QString();

    playerDefending = false;
    playerTurn = false;

    enemy->takeDamage(player.strength);

    if (enemy->isDead()) {
        gameOver = true;
        return "Você derrotou o inimigo!";
    }

    return "Você atacou o inimigo!";
}

QString CombatRoom::playerDefend(Player &player) {
    if (!playerTurn || gameOver)
        return QString();

    playerDefending = true;
    playerTurn = false;
    return "Você está defendendo!";
}

QString CombatRoom::playerUseItem(Player &player, const QString &item) {
    if (!playerTurn || gameOver)
        return QString();

    if (!player.hasItem(item))
        return "Item não disponível.";

    if (player.useItem(item)) {
        playerDefending = false;
        playerTurn = false;
        return QString("Você usou o item: %1").arg(item);
    }

    return "Não foi possível usar o item.";
}

QString CombatRoom::playerFlee(Player &player) {
    if (!playerTurn || gameOver)
        return QString();

    playerTurn = false;

    if (QRandomGenerator::global()->bounded(100) < 50) {
        gameOver = true;
        return "Fuga bem sucedida!";
    } else {
        return "Falhou! O inimigo contra-ataca!";
    }
}

QString CombatRoom::enemyAttack(Player &player, Enemy *&enemy) {
    if (playerTurn || gameOver || enemy == nullptr)
        return QString();

    int dmg = playerDefending ? enemy->strength / 2 : enemy->strength;
    player.takeDamage(dmg);
    playerDefending = false;

    if (player.isDead()) {
        gameOver = true;
        return "Você morreu! Game Over!";
    }

    playerTurn = true;
    return "O inimigo atacou você!";
}

