# Implementação

>[!NOTE]
> Relatar o processo de implementação do problema, incluindo as ferramentas e bibliotecas utilizadas.

---

## Ferramentas e Tecnologias Utilizadas

- **Linguagem**: C++
- **Framework gráfico**: [Qt Creator (Qt 5+)](https://www.qt.io/)
- **Paradigma**: Programação Orientada a Objetos
- **Recursos Qt usados**:
  - `QLabel`, `QPushButton`, `QMessageBox`, `QInputDialog`
  - `QVBoxLayout`, `QHBoxLayout` para organização visual
  - `QRandomGenerator` para geração de inimigos e salas
- **Controle de versão**: Git + GitHub

---

## Estrutura de Implementação

A arquitetura está dividida em módulos distintos:

- `Character` → classe base para entidades vivas (player e inimigos)
  - `Player` com inventário e ações
  - `Enemy` gerado dinamicamente com atributos randômicos

- `Room` → classe base abstrata para salas
  - `CombatRoom`, `StoryRoom`, `BonfireRoom`, `EquipmentRoom`, `BossRoom`

- `RoomFactory` → gera salas com base no `roomCount`, evitando repetições

- `GameWindow` → interface principal do jogo, renderiza telas e controla fluxo

---

## Funcionalidades Principais

- Combate por turnos com ações de ataque, defesa, fuga e uso de item
- Inventário dinâmico com lógica condicional (cura, lâmina especial)
- Escolhas narrativas em `StoryRoom` e bifurcações temáticas via `promptForkChoice`
- Progressão com salas fixas no início e aleatórias depois
- Finais múltiplos com janela de decisão após derrota do chefe

---

<div align="center">

[Retroceder](projeto.md) • [Testes](testes.md)

</div>
