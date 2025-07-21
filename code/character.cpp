#include "character.h"

Character::Character(int hp, int strength) : hp(hp), maxHp(hp), strength(strength) {}

void Character::takeDamage(int dmg) {
    hp -= dmg;
    if (hp < 0) hp = 0;
}

bool Character::isDead() const {
    return hp <= 0;
}