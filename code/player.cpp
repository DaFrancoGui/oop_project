#include "player.h"
#include <algorithm>

Player::Player() : Character(100, 20) {
    addItem("Poção Média de cura (+30)");
    addItem("Poção Média de cura (+30)");
}

void Player::heal(int value) {
    hp = std::min(maxHp, hp + value);
}

void Player::upgrade() {
    strength += 5;
}

void Player::addStrength(int amount) {
    strength += amount;
}

void Player::addMaxHp(int amount) {
    maxHp += amount;
    hp += amount;
    hp = std::min(hp, maxHp);
}

void Player::addItem(const QString& item) {
    inventory.append(item);
}

bool Player::removeItem(const QString& item) {
    return inventory.removeOne(item);
}

bool Player::hasItem(const QString& item) const {
    return inventory.contains(item);
}

QStringList Player::getInventory() const {
    return inventory;
}

bool Player::useItem(const QString& item) {
    if (!hasItem(item))
        return false;

    if (item.contains("cura", Qt::CaseInsensitive)) {
        heal(30);
        removeItem(item);
        return true;
    }

    if (item.contains("Lâmina da Purgação", Qt::CaseInsensitive)) {
        // Tratado em CombatRoom
        return false;
    }

    return false;
}
