#include "gamewindow.h"

#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>

#include "player.h"
#include "enemy.h"
#include "combatroom.h"
#include "roomfactory.h"
#include "storyroom.h"
#include "room.h"
#include "bossroom.h"
#include "bonfireroom.h"
#include "equipmentroom.h"

Player& GameWindow::getPlayer() {
    return player;
}

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent), enemy(nullptr), gameOver(false), bossRoom(false)
{
    setWindowTitle("Oração do Lich — RPG Tático");
    resize(500, 400);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignHCenter);
    mainLayout->setContentsMargins(60, 40, 60, 40); // respiro visual expandido
    setLayout(mainLayout);

    createInitialScreen();
}

void GameWindow::clearMainLayout() {
    while (QLayoutItem* item = mainLayout->takeAt(0)) {
        if (QWidget* w = item->widget()) {
            w->deleteLater();
        } else if (QLayout* layout = item->layout()) {
            while (QLayoutItem* child = layout->takeAt(0)) {
                if (QWidget* cw = child->widget())
                    cw->deleteLater();
                delete child;
            }
            delete layout;
        }
    }
}

void GameWindow::createInitialScreen() {
    clearMainLayout();

    if (enemy) {
        delete enemy;
        enemy = nullptr;
    }

    currentRoom.reset();
    player = Player();
    bossRoom = false;
    gameOver = false;

    // 🏷️ Título temático
    auto* title = new QLabel("ORAÇÃO DO LICH", this);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 28px; font-weight: bold; color: #DEDEDE;");

    // 💬 Subtítulo narrativo
    auto* subtitle = new QLabel("A cada passo no castelo, a luz se apaga...\nEscolha bem. Nem toda vitória brilha.", this);
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setWordWrap(true);
    subtitle->setStyleSheet("font-size: 14px; font-style: italic; color: #C0C0C0;");
    subtitle->setMinimumWidth(500);
    subtitle->setMaximumWidth(500);

    // 🎮 Botão de início estilizado
    auto* start = new QPushButton("Iniciar Jornada", this);
    start->setFixedWidth(180);
    start->setMinimumHeight(40);
    start->setStyleSheet(
        "font-size: 16px; font-weight: bold; padding: 10px;"
        "background-color: #444; color: white; border: 2px solid #888;"
        "border-radius: 6px;"
        );

    // 📦 Centralização com wrapper horizontal
    QWidget* textWrapper = new QWidget(this);
    QVBoxLayout* wrapperLayout = new QVBoxLayout(textWrapper);
    wrapperLayout->setAlignment(Qt::AlignHCenter);
    wrapperLayout->setSpacing(12);
    wrapperLayout->addWidget(title);
    wrapperLayout->addWidget(subtitle);

    mainLayout->addStretch();
    mainLayout->addWidget(textWrapper);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(start, 0, Qt::AlignHCenter);
    mainLayout->addStretch();

    connect(start, &QPushButton::clicked, this, &GameWindow::nextRoom);
}


void GameWindow::nextRoom() {
    if (gameOver) return;

    clearMainLayout();

    if (enemy) {
        delete enemy;
        enemy = nullptr;
    }

    currentRoom.reset();

    static int roomCount = 0;
    roomCount++;

    currentRoom = RoomFactory::createRoom(roomCount, this);
    lastWasEquipmentRoom = dynamic_cast<EquipmentRoom*>(currentRoom.get()) != nullptr;

    bossRoom = (roomCount == 10);

    currentRoom->enter(player, enemy);

    createRoomScreen();
}

void GameWindow::createRoomScreen() {
    clearMainLayout();

    // 💀 Sala do boss
    bossRoom = dynamic_cast<BossRoom*>(currentRoom.get()) != nullptr;
    if (bossRoom) {
        QMessageBox::information(this, "Rei Lich Mortius",
                                 "'Você ousa entrar em meu domínio, mortal?\nQue seus ossos sirvam à minha legião eternamente...'");
    }

    // ⚔️ Sala de combate
    if (CombatRoom* cRoom = dynamic_cast<CombatRoom*>(currentRoom.get())) {
        currentRoom->enter(player, enemy);

        combatLabel = new QLabel("Prepare-se para o combate!", this);
        combatLabel->setWordWrap(true);
        combatLabel->setAlignment(Qt::AlignCenter);
        combatLabel->setStyleSheet("font-size: 14px;");
        combatLabel->setMinimumWidth(500);
        combatLabel->setMaximumWidth(500);
        combatLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

        QWidget* combatWrapper = new QWidget(this);
        QHBoxLayout* layout = new QHBoxLayout(combatWrapper);
        layout->addStretch();
        layout->addWidget(combatLabel);
        layout->addStretch();
        mainLayout->addWidget(combatWrapper);
        mainLayout->addSpacing(15);

        const int btnWidth = 160;

        attackBtn = new QPushButton("Atacar", this);
        defendBtn = new QPushButton("Defender", this);
        itemBtn = new QPushButton("Usar Item", this);
        fleeBtn = new QPushButton("Fugir", this);

        attackBtn->setFixedWidth(btnWidth);
        defendBtn->setFixedWidth(btnWidth);
        itemBtn->setFixedWidth(btnWidth);
        fleeBtn->setFixedWidth(btnWidth);

        connect(attackBtn, &QPushButton::clicked, this, &GameWindow::playerAttack);
        connect(defendBtn, &QPushButton::clicked, this, &GameWindow::playerDefend);
        connect(itemBtn, &QPushButton::clicked, this, &GameWindow::playerUseItem);
        connect(fleeBtn, &QPushButton::clicked, this, &GameWindow::playerFlee);

        QVBoxLayout* btnColLayout = new QVBoxLayout;
        btnColLayout->setAlignment(Qt::AlignHCenter);
        btnColLayout->setSpacing(12);
        btnColLayout->addWidget(attackBtn);
        btnColLayout->addWidget(defendBtn);
        btnColLayout->addWidget(itemBtn);
        btnColLayout->addWidget(fleeBtn);

        mainLayout->addLayout(btnColLayout);
        updateCombatText("Um inimigo se aproxima...");
    }

    // 📜 Sala narrativa
    else if (StoryRoom* sRoom = dynamic_cast<StoryRoom*>(currentRoom.get())) {
        currentRoom->enter(player, enemy);

        const auto& choices = sRoom->getChoices();

        QVBoxLayout* storyLayout = new QVBoxLayout;
        storyLayout->setAlignment(Qt::AlignHCenter);
        storyLayout->setSpacing(15);

        QLabel* descLabel = new QLabel(currentRoom->description(), this);
        descLabel->setWordWrap(true);
        descLabel->setAlignment(Qt::AlignCenter);
        descLabel->setStyleSheet("font-size: 16px; font-weight: bold;");
        descLabel->setMinimumWidth(500);
        descLabel->setMaximumWidth(500);
        descLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

        storyLayout->addWidget(descLabel);

        for (const auto& choice : choices) {
            QPushButton* btn = new QPushButton(choice.first, this);
            btn->setFixedWidth(320);
            btn->setMinimumHeight(38);
            btn->setStyleSheet("font-size: 14px;");
            connect(btn, &QPushButton::clicked, this, [func = choice.second]() { func(); });
            storyLayout->addWidget(btn, 0, Qt::AlignHCenter);
        }

        QWidget* storyWrapper = new QWidget(this);
        storyWrapper->setLayout(storyLayout);

        mainLayout->addStretch();
        mainLayout->addWidget(storyWrapper);
        mainLayout->addStretch();
    }

    // 🛡️ Sala sem escolhas
    else {
        currentRoom->enter(player, enemy);

        QVBoxLayout* noChoiceLayout = new QVBoxLayout;
        noChoiceLayout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        noChoiceLayout->setSpacing(20);

        QLabel* tipLabel = new QLabel(
            "O ambiente permanece em silêncio, mas você sente que algo te observa...\nA jornada continua.",
            this);
        tipLabel->setWordWrap(true);
        tipLabel->setAlignment(Qt::AlignCenter);
        tipLabel->setStyleSheet("font-size: 13px; font-style: italic;");
        tipLabel->setMinimumWidth(500);
        tipLabel->setMaximumWidth(500);
        tipLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

        noChoiceLayout->addWidget(tipLabel, 0, Qt::AlignCenter);

        QPushButton* continueBtn = new QPushButton("Continuar", this);
        continueBtn->setFixedWidth(220);
        continueBtn->setMinimumHeight(38);
        continueBtn->setStyleSheet("font-size: 14px; font-weight: bold;");
        connect(continueBtn, &QPushButton::clicked, this, &GameWindow::nextRoom);

        noChoiceLayout->addWidget(continueBtn, 0, Qt::AlignCenter);

        QWidget* noChoiceWrapper = new QWidget(this);
        noChoiceWrapper->setLayout(noChoiceLayout);

        mainLayout->addStretch();
        mainLayout->addWidget(noChoiceWrapper, 0, Qt::AlignCenter);
        mainLayout->addStretch();

    }
}


void GameWindow::updateCombatText(const QString& msg) {
    if (!combatLabel)
        return;

    CombatRoom* cRoom = dynamic_cast<CombatRoom*>(currentRoom.get());
    if (!cRoom || !enemy)
        return;

    QString text;

    if (cRoom->combatOver()) {
        text = msg;
    } else if (!cRoom->isPlayerTurn()) {
        text = "Turno do inimigo...\n\n" + msg;
    } else {
        text = QString(
                   "%1 (HP: %2 / Força: %3)%4\n"
                   "%5 (HP: %6 / Dano: %7)\n\n"
                   "%8")
                   .arg("Você")
                   .arg(player.hp)
                   .arg(player.strength)
                   .arg(cRoom->isPlayerDefending() ? " [Defendendo]" : "")
                   .arg(enemy->name.isEmpty() ? "Inimigo" : enemy->name)
                   .arg(enemy->hp)
                   .arg(enemy->strength)
                   .arg(msg);
    }

    combatLabel->setText(text);
    combatLabel->setAlignment(Qt::AlignCenter);
    combatLabel->setStyleSheet("font-size: 13px; font-style: italic;");

}

void GameWindow::handleCombatEnd(const QString& msg) {
    CombatRoom* cRoom = dynamic_cast<CombatRoom*>(currentRoom.get());
    if (!cRoom) return;

    clearMainLayout();

    bool venceuChefe = bossRoom && enemy && enemy->isDead();
    bool morreu = player.isDead();
    gameOver = morreu || venceuChefe;

    QLabel* lbl = new QLabel(this);
    lbl->setWordWrap(true);
    lbl->setAlignment(Qt::AlignCenter);
    lbl->setStyleSheet("font-size: 15px;");

    QString finalMsg;

    // 💀 Derrota do jogador
    if (morreu) {
        finalMsg = "Você foi derrotado...\n\nSua alma é consumida pelo Rei Lich Mortius.\nAgora, você está preso em um ciclo eterno de sofrimento nas mãos frias do mestre das trevas.";
    }

    // 🏆 Vitória contra o boss
    else if (venceuChefe) {
        finalMsg = "Você derrotou o Rei Lich Mortius!\n\nO castelo treme... a escuridão se dissipa.\nMas algo permanece: uma decisão derradeira.";

        // ⚖️ Escolha final narrativa
        QStringList finais = {
            "Ficar com todo o ouro e assumir o trono sombrio como novo Lich",
            "Libertar as almas e fugir do castelo com sua humanidade intacta"
        };

        bool ok = false;
        QString escolha = QInputDialog::getItem(this,
                                                "Última Decisão",
                                                "O que você fará?",
                                                finais, 0, false, &ok);

        if (ok && escolha.contains("ouro", Qt::CaseInsensitive)) {
            finalMsg += "\n\nVocê se senta no trono de ossos, rodeado por ouro maldito...\nA eternidade te abraça enquanto sua alma se esvai.\n\nVocê é agora o novo Lich King.";
        } else {
            finalMsg += "\n\nVocê quebra as correntes místicas.\nAs almas aprisionadas se elevam aos céus...\n\nVocê escapa como herói — marcado, mas livre.";
        }
    }

    // ⚔️ Vitória contra inimigos comuns
    else {
        finalMsg = "Você venceu o combate. O inimigo caiu diante da sua força.\nPrepare-se para continuar sua jornada.";
    }

    lbl->setText(finalMsg);
    mainLayout->addStretch();
    mainLayout->addWidget(lbl, 0, Qt::AlignHCenter);
    mainLayout->addSpacing(20);

    QPushButton* btn;
    if (morreu || venceuChefe) {
        btn = new QPushButton("Jogar novamente", this);
        connect(btn, &QPushButton::clicked, this, &GameWindow::restartGame);
    } else {
        btn = new QPushButton("Continuar", this);
        connect(btn, &QPushButton::clicked, this, &GameWindow::nextRoom);
        gameOver = false;
    }

    btn->setFixedWidth(220);
    btn->setMinimumHeight(40);
    btn->setStyleSheet("font-size: 14px; font-weight: bold;");
    mainLayout->addWidget(btn, 0, Qt::AlignHCenter);
    mainLayout->addStretch();

    if (enemy) {
        delete enemy;
        enemy = nullptr;
    }
    currentRoom.reset();
}


void GameWindow::playerDefend() {
    CombatRoom* cRoom = dynamic_cast<CombatRoom*>(currentRoom.get());
    if (!cRoom || !enemy || gameOver)
        return;

    if (!cRoom->isPlayerTurn()) return;

    QString msg = cRoom->playerDefend(player);
    updateCombatText(msg);

    QTimer::singleShot(600, this, [=]() {
        QString enemyMsg = cRoom->enemyAttack(player, enemy);
        updateCombatText(enemyMsg);

        if (cRoom->combatOver()) {
            handleCombatEnd(enemyMsg);
        }
    });
}


void GameWindow::playerAttack() {
    CombatRoom* cRoom = dynamic_cast<CombatRoom*>(currentRoom.get());
    if (!cRoom || !enemy || gameOver)
        return;

    if (!cRoom->isPlayerTurn()) return;

    QString msg = cRoom->playerAttack(player, enemy);
    updateCombatText(msg);

    if (cRoom->combatOver()) {
        handleCombatEnd(msg);
        return;
    }

    QTimer::singleShot(600, this, [=]() {
        QString enemyMsg = cRoom->enemyAttack(player, enemy);
        updateCombatText(enemyMsg);

        if (cRoom->combatOver()) {
            handleCombatEnd(enemyMsg);
        }
    });
}

void GameWindow::playerUseItem() {
    CombatRoom* cRoom = dynamic_cast<CombatRoom*>(currentRoom.get());
    if (!cRoom || !enemy || gameOver)
        return;

    if (!cRoom->isPlayerTurn()) return;

    QStringList inv = player.getInventory();
    if (inv.isEmpty()) {
        QMessageBox::information(this, "Inventário", "Nenhum item disponível.");
        return;
    }

    bool ok = false;
    QString choice = QInputDialog::getItem(this, "Usar Item", "Escolha um item:", inv, 0, false, &ok);
    if (!ok) return;

    // ✅ Detecção especial da Lâmina
    if (choice.contains("Lâmina da Purgação", Qt::CaseInsensitive) && bossRoom && enemy) {
        QMessageBox::information(this, "Purgação", "Você empunha a Lâmina da Purgação. A luz consome o Lich King em um grito eterno.");
        player.removeItem(choice);
        enemy->hp = 0;
        handleCombatEnd("O Lich King foi purgado da existência!");
        return;
    }

    QString msg = cRoom->playerUseItem(player, choice);
    updateCombatText(msg);

    if (cRoom->combatOver()) {
        handleCombatEnd(msg);
        return;
    }

    QTimer::singleShot(600, this, [=]() {
        QString enemyMsg = cRoom->enemyAttack(player, enemy);
        updateCombatText(enemyMsg);
        if (cRoom->combatOver()) {
            handleCombatEnd(enemyMsg);
        }
    });
}


void GameWindow::playerFlee() {
    CombatRoom* cRoom = dynamic_cast<CombatRoom*>(currentRoom.get());
    if (!cRoom || !enemy || gameOver)
        return;

    if (!cRoom->isPlayerTurn()) return;

    QString msg = cRoom->playerFlee(player);
    updateCombatText(msg);

    if (msg == "Fuga bem sucedida!") {
        QTimer::singleShot(600, this, &GameWindow::nextRoom);
    } else {
        QTimer::singleShot(600, this, [=]() {
            QString enemyMsg = cRoom->enemyAttack(player, enemy);
            updateCombatText(enemyMsg);

            if (cRoom->combatOver()) {
                handleCombatEnd(enemyMsg);
            }
        });
    }
}

void GameWindow::setForkOptions(std::vector<std::unique_ptr<Room>> options) {
    forkRooms = std::move(options);
}

void GameWindow::promptForkChoice(const QString& promptText) {
    clearMainLayout();

    // Bloco principal vertical
    QVBoxLayout* wrapperLayout = new QVBoxLayout;
    wrapperLayout->setAlignment(Qt::AlignHCenter);
    wrapperLayout->setSpacing(20);

    // Texto narrativo
    QLabel* prompt = new QLabel(promptText, this);
    prompt->setWordWrap(true);
    prompt->setAlignment(Qt::AlignCenter);
    prompt->setStyleSheet("font-size: 16px; font-weight: bold;");
    prompt->setMinimumWidth(500);
    prompt->setMaximumWidth(500);
    prompt->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

    wrapperLayout->addWidget(prompt);

    // Botões
    for (size_t i = 0; i < forkRooms.size(); ++i) {
        QString label;

        if (roomCount == 2) {
            label = (i == 0)
            ? "Você ouve o som de aço colidindo — uma batalha à frente."
            : "O aroma de brasas reacendidas vem de uma porta antiga...";
        } else if (roomCount == 3) {
            label = (i == 0)
            ? "Há uma energia mágica vibrando do caminho à esquerda..."
            : "Sussurros enigmáticos ecoam do corredor da direita...";
        } else if (dynamic_cast<CombatRoom*>(forkRooms[i].get())) {
            label = "Trilha onde presenças hostis se agitam...";
        } else if (dynamic_cast<BonfireRoom*>(forkRooms[i].get())) {
            label = "Caminho onde calor antigo ainda pulsa...";
        } else if (dynamic_cast<EquipmentRoom*>(forkRooms[i].get())) {
            label = "Corredor esquecido, onde ecoa poder perdido...";
        } else if (dynamic_cast<StoryRoom*>(forkRooms[i].get())) {
            label = "Passagem de murmúrios indecifráveis...";
        } else {
            label = "Estrada oculta, envolta em mistério...";
        }

        QPushButton* btn = new QPushButton(label, this);
        btn->setFixedWidth(320);
        btn->setMinimumHeight(38);
        btn->setStyleSheet("font-size: 14px;");
        connect(btn, &QPushButton::clicked, this, [=]() {
            currentRoom = std::move(forkRooms[i]);
            forkRooms.clear();
            currentRoom->enter(player, enemy);
            createRoomScreen();
        });

        wrapperLayout->addWidget(btn, 0, Qt::AlignHCenter);
    }

    // Envolve tudo num QWidget
    QWidget* wrapper = new QWidget(this);
    wrapper->setLayout(wrapperLayout);

    // Aplica espaçamento vertical como em outras telas
    mainLayout->addStretch();
    mainLayout->addWidget(wrapper);
    mainLayout->addStretch();
}


void GameWindow::restartGame() {
    static int roomCount = 0;
    roomCount = 0;
    createInitialScreen();
}
