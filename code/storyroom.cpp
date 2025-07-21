#include "storyroom.h"

StoryRoom::StoryRoom(const QString& text, const QList<QPair<QString, std::function<void()>>>& choices)
    : storyText(text), options(choices) {}

QString StoryRoom::description() const {
    return storyText;
}

void StoryRoom::enter(Player&, Enemy*& enemy) {
    enemy = nullptr;
}

QList<QPair<QString, std::function<void()>>> StoryRoom::getChoices() const {
    return options;
}
