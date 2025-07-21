#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
public:
    int hp;
    int maxHp;
    int strength;

    Character(int hp, int strength);
    virtual void takeDamage(int dmg);
    virtual bool isDead() const;
};

#endif