#include "equipmentroom.h"
#include "player.h"
#include <QInputDialog>
#include <QRandomGenerator>

QString EquipmentRoom::description() const {
    return "Sala de Equipamentos Místicos";
}

void EquipmentRoom::enter(Player &player, Enemy *&) {
    struct Equipment {
        QString name;
        QString effect;
        int strengthBonus = 0;
        int hpBonus = 0;
    };

    QList<Equipment> all = {
        {"Espada Rúnica", "+10 Força", 10, 0},
        {"Elmo de Aço Antigo", "+20 Vida Máxima", 0, 20},
        {"Botas Élficas", "+5 Força, +10 Vida", 5, 10},
        {"Machado Flamejante", "+15 Força, -10 Vida", 15, -10},
        {"Armadura do Guardião", "+30 Vida Máx", 0, 30},
        {"Adaga Sombria", "+8 Força", 8, 0}
    };

    int i1 = QRandomGenerator::global()->bounded(all.size());
    int i2;
    do {
        i2 = QRandomGenerator::global()->bounded(all.size());
    } while (i2 == i1);

    const Equipment &e1 = all[i1];
    const Equipment &e2 = all[i2];

    QStringList options = {
        QString("%1 (%2)").arg(e1.name, e1.effect),
        QString("%1 (%2)").arg(e2.name, e2.effect)
    };

    bool ok = false;
    QString choice = QInputDialog::getItem(nullptr, "Escolha um Equipamento",
                                           "Você encontrou dois equipamentos. Escolha um:",
                                           options, 0, false, &ok);
    if (!ok) return;

    const Equipment *selected = choice.contains(e1.name) ? &e1 : &e2;

    if (selected) {
        if (selected->strengthBonus)
            player.addStrength(selected->strengthBonus);
        if (selected->hpBonus) {
            player.addMaxHp(selected->hpBonus);
            player.heal(selected->hpBonus);
        }
    }
}
