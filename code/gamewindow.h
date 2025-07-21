#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <memory>
#include "player.h"
#include "room.h"

class Player;
class Enemy;
class Room;
class CombatRoom;

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    Player& getPlayer();
    void nextRoom();
    void createInitialScreen();
    void setForkOptions(std::vector<std::unique_ptr<Room>> options);
    void promptForkChoice(const QString& promptText);
    bool lastWasEquipmentRoom = false;

private slots:
    void playerAttack();
    void playerDefend();
    void playerUseItem();
    void playerFlee();
    void restartGame();

private:
    void createRoomScreen();
    void clearMainLayout();

    void updateCombatText(const QString &msg);
    void handleCombatEnd(const QString &msg);

    QVBoxLayout *mainLayout;

    Player player;
    Enemy *enemy = nullptr;

    std::unique_ptr<Room> currentRoom;
    std::vector<std::unique_ptr<Room>> forkRooms;

    QLabel *combatLabel = nullptr;

    QPushButton *attackBtn = nullptr;
    QPushButton *defendBtn = nullptr;
    QPushButton *itemBtn = nullptr;
    QPushButton *fleeBtn = nullptr;

    bool gameOver = false;
    bool bossRoom = false;

    int roomCount = 0;
};

#endif // GAMEWINDOW_H
