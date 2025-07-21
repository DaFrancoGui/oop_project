#ifndef STORYROOM_H
#define STORYROOM_H

#include "room.h"
#include <QString>
#include <QList>
#include <QPair>
#include <functional>

class StoryRoom : public Room {
public:
    StoryRoom(const QString& text, const QList<QPair<QString, std::function<void()>>>& choices);

    QString description() const override;
    void enter(Player &player, Enemy *&enemy) override;
    QList<QPair<QString, std::function<void()>>> getChoices() const;

private:
    QString storyText;
    QList<QPair<QString, std::function<void()>>> options;
};

#endif
