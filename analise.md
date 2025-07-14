# Análise orientada a objeto
> [!NOTE]
> A **análise** orientada a objeto consiste na descrição do problema a ser tratado, duas primeiras etapas da tabela abaixo, a definição de casos de uso e a definição do domínio do problema.

## Descrição Geral do domínio do problema

O presente projeto propõe o desenvolvimento de um jogo estilo **RPG de turnos** com interface gráfica via **Qt Creator**, utilizando os conceitos de programação orientada a objetos. O jogo se passa em uma série de salas interconectadas que podem conter inimigos, tesouros ou elementos narrativos. O jogador poderá se mover entre as salas, enquanto participa de combates por turnos contra inimigos em batalhas inspiradas no modelo de Pokémon, de forma simplificada.

As primeiras salas são fixas, mas as subsequentes são geradas com base em modelos pré-definidos, com variações introduzidas a partir de uma semente (seed), criando variações procedurais limitadas. A progressão do jogador pode levá-lo rapidamente ao fim do jogo ou forçá-lo a explorar mais salas, dependendo de suas decisões.

### Requisitos Funcionais

- O jogador poderá:
  - Mover-se entre salas.
  - Iniciar e participar de combates por turnos.
  - Coletar e usar itens.
  - Interagir com elementos narrativos da história.
- O sistema gerará salas proceduralmente com base em modelos fixos e variações por seed.
- O combate seguirá um modelo de turnos com três ações principais: atacar, defender, usar item, ou fugir.
- Sistema simples de combate e progressão.

### Requisitos Não-Funcionais

- Interface gráfica desenvolvida com Qt Creator.
- Arquitetura orientada a objetos.
- Código modular e expansível.
- Interface amigável e responsiva.

---

## Diagrama de Casos de Uso

**Ator:** Jogador

**Casos de Uso Principais:**

- **Explorar sala**: O jogador pode caminhar por salas diferentes, com conteúdos diversos (inimigos, tesouros e elementos narrativos).
- **Avançar para próxima sala**: Move o jogador para uma nova sala (fixa ou procedural).
- **Iniciar combate**: Caso a sala contenha um inimigo, inicia-se o combate por turnos.
- **Executar ação no combate**: Durante o combate, o jogador pode atacar, defender, fugir ou usar um item.
- **Coletar item**: Se a sala contiver um item, o jogador pode coletá-lo.
- **Interagir com narrativa**: Permite ler mensagens ou eventos ligados à história do jogo.

<div align="center">
    <img src="img/Diagramas/Diagrama de caso de uso.png" 
         width="70%" 
         style="padding: 10px">
</div>

## Diagrama de Domínio do problema

<div align="center">
    <img src="img/Diagramas/Classe UML.png" 
         width="70%" 
         style="padding: 10px">
</div>

<div align="center">

[Retroceder](README.md) | [Avançar](projeto.md)

</div>
