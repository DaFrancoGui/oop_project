#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include <QStringList>

class Player : public Character
{
public:
    Player();

    void heal(int value = 30);
    void upgrade();
    void addStrength(int amount);
    void addMaxHp(int amount);

    void addItem(const QString& item);
    bool removeItem(const QString& item);
    bool hasItem(const QString& item) const;
    QStringList getInventory() const;

    bool useItem(const QString& item);

private:
    QStringList inventory;
};

#endif // PLAYER_H
