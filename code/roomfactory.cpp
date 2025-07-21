#include "roomfactory.h"
#include "gamewindow.h"
#include "storyroom.h"
#include "combatroom.h"
#include "equipmentroom.h"
#include "bonfireroom.h"
#include "bossroom.h"
#include <QRandomGenerator>
#include <QMessageBox>

std::unique_ptr<Room> RoomFactory::createRoom(int roomCount, GameWindow* window) {
    if (roomCount == 1) {
        return std::make_unique<StoryRoom>(
            "Você é um batedor da Guilda dos Ladrões.\n\nDescobriu rumores sobre um castelo abandonado repleto de ouro.\nApesar dos avisos, parte sozinho atrás da fortuna.",
            QList<QPair<QString, std::function<void()>>>{
                { "Partir para o castelo", [window]() {
                     if (window) window->nextRoom();
                 }}
            });
    }

    if (roomCount == 2) {
        return std::make_unique<StoryRoom>(
            "Você cruza os portões antigos.\n\nVozes sussurram entre as pedras...\n\nDuas trilhas se revelam:\n• Uma escura e úmida\n• Outra iluminada e silenciosa",
            QList<QPair<QString, std::function<void()>>>{
                { "Trilha escura e úmida", [window]() {
                     if (window) {
                         std::vector<std::unique_ptr<Room>> options;
                         options.push_back(std::make_unique<CombatRoom>());
                         options.push_back(std::make_unique<BonfireRoom>());
                         window->setForkOptions(std::move(options));
                         window->promptForkChoice("As sombras te cercam...\n\nEscolha por onde continuar:");
                     }
                 }},
                { "Trilha iluminada e silenciosa", [window]() {
                     if (window) {
                         std::vector<std::unique_ptr<Room>> options;
                         options.push_back(std::make_unique<EquipmentRoom>());
                         options.push_back(std::make_unique<CombatRoom>());
                         window->setForkOptions(std::move(options));
                         window->promptForkChoice("A luz revela corredores antigos...\n\nEscolha seu caminho:");
                     }
                 }}
            });
    }

    if (roomCount == 3) {
        return std::make_unique<StoryRoom>(
            "Você entra numa sala circular, silenciosa como um túmulo.\n\nTrês passagens se abrem diante de você.\n\nNo centro, um obelisco pulsante sussurra que cada caminho carrega um destino imprevisível.",
            QList<QPair<QString, std::function<void()>>>{
                { "Corredor flamejante", [window]() {
                     if (window) {
                         std::vector<std::unique_ptr<Room>> options;
                         options.push_back(std::make_unique<CombatRoom>());
                         options.push_back(std::make_unique<CombatRoom>());
                         window->setForkOptions(std::move(options));
                         window->promptForkChoice("A temperatura sobe...\n\nChamas dançam entre pilares rachados.");
                     }
                 }},
                { "Passagem coberta por fungos", [window]() {
                     if (window) {
                         std::vector<std::unique_ptr<Room>> options;
                         options.push_back(std::make_unique<BonfireRoom>());
                         options.push_back(std::make_unique<EquipmentRoom>());
                         window->setForkOptions(std::move(options));
                         window->promptForkChoice("Musgos misteriosos cobrem as paredes...\n\nO silêncio domina.");
                     }
                 }},
                { "Porta com selo de caveira", [window]() {
                     if (window) {
                         std::vector<std::unique_ptr<Room>> options;
                         options.push_back(std::make_unique<StoryRoom>(
                             "Você encontra um baú lacrado.\n\nDentro, repousa uma lâmina enferrujada.\nSua aparência não é convidativa, mas você sente uma\naura estranha e uma súplica quase \ninaudível implorando que você a pegue.",
                             QList<QPair<QString, std::function<void()>>>{
                                 { "Pegar a Lâmina", [window]() {
                                      if (window) {
                                          window->getPlayer().addItem("Lâmina da Purgação");
                                          QMessageBox::information(nullptr, "Item Obtido",
                                                                   "Você obteve a Lâmina da Purgação!\nEla pode eliminar o Lich King com um único golpe.");
                                          window->nextRoom();
                                      }
                                  }},
                                 { "Ignorar o baú e seguir", [window]() {
                                      if (window) window->nextRoom();
                                  }}
                             }));
                         options.push_back(std::make_unique<CombatRoom>());
                         window->setForkOptions(std::move(options));
                         window->promptForkChoice("O selo se dissolve...\n\nDois destinos se revelam.");
                     }
                 }}
            });
    }

    if (roomCount == 5) {
        return std::make_unique<StoryRoom>(
            "Você vê um retrato antigo empoeirado.\n\nUm homem nobre em trono dourado segura um crânio.\n\nEcos de poder parecem emanar da pintura...",
            QList<QPair<QString, std::function<void()>>>{
                { "Refletir sobre o quadro", [window]() {
                     QMessageBox::information(nullptr, "Reflexão", "Uma leve dor de cabeça te atinge...\nComo se algo tentasse te impedir de lembrar.");
                     if (window) window->nextRoom();
                 }},
                { "Ignorar e seguir", [window]() {
                     if (window) window->nextRoom();
                 }}
            });
    }

    if (roomCount == 7) {
        return std::make_unique<StoryRoom>(
            "Você encontra um templo subterrâneo coberto de musgo.\n\nZumbis rezam em silêncio diante de uma pedra central.\n\nHá inscrições entalhadas em linguagem esquecida...",
            QList<QPair<QString, std::function<void()>>>{
                { "Decifrar inscrições", [window]() {
                     QMessageBox::information(nullptr, "Lore",
                                              "O texto profetiza:\n\n'Aquele que toca na espada maldita jamais envelhece...'\n\nMas sangra por dentro.");
                     if (window) window->nextRoom();
                 }},
                { "Evitar a pedra e continuar", [window]() {
                     if (window) window->nextRoom();
                 }}
            });
    }

    if (roomCount == 9) {
        return std::make_unique<StoryRoom>(
            "Você chega a uma porta adornada com símbolos de morte e renascimento.\n\nO clima pesa — este parece ser o limiar do último desafio.",
            QList<QPair<QString, std::function<void()>>>{
                { "Abrir a porta", [window]() {
                     QMessageBox::information(nullptr, "Porta Final",
                                              "Você toca a maçaneta.\n\nA porta se abre lentamente, revelando o Lich King:\n\n'HAHAHAHA... OLHEM MEUS PEQUENOS,\nMAIS UM FILHO PARA COMPLETAR NOSSA FAMÍLIA'");
                     if (window) window->nextRoom();
                 }},
                { "Dar meia volta", [window]() {
                     QMessageBox::information(nullptr, "Destino selado",
                                              "Você tenta fugir, mas uma mão gelada te segura...\n\nSua visão escurece.\n\n'Você não vai a lugar nenhum.'");
                     if (window) window->createInitialScreen();
                 }}
            });
    }

    if (roomCount == 10)
        return std::make_unique<BossRoom>();

    // 🎲 Salas aleatórias com trava para evitar sequência de EquipmentRoom
    bool evitarEquipment = window && window->lastWasEquipmentRoom;
    int rand = QRandomGenerator::global()->bounded(100);
    if (evitarEquipment && rand < 70) rand += 20;

    if (rand < 50) return std::make_unique<CombatRoom>();
    if (rand < 70) return std::make_unique<EquipmentRoom>();
    if (rand < 90) return std::make_unique<BonfireRoom>();

    return std::make_unique<CombatRoom>();
}
