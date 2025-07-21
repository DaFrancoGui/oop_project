# Testes

>[!NOTE]
> Relatar o processo de testes do sistema, especificando quais testes foram realizados e os resultados obtidos.

---

## Estratégia de Testes

Durante o desenvolvimento, foram realizados diversos testes para validar o comportamento das classes, a interface gráfica e a lógica de progressão do jogo. Os testes abordaram tanto a funcionalidade quanto a experiência visual e narrativa.

---

### Testes de Combate

- Verificação de turnos alternados entre jogador e inimigo.
- Teste de ações: ataque, defesa, uso de item e fuga.
- Lógica de dano e defesa correta (redução de dano em defesa).
- Teste de fim de combate com vitória, derrota e combate contra chefe.

---

### Testes de Salas

- `RoomFactory` gera salas corretamente conforme `roomCount`.
- Prevenção de salas repetidas de equipamento (dois `EquipmentRoom` seguidos):
  - Esse problema foi detectado durante os testes.
  - Solução aplicada: uso de flag `lastWasEquipmentRoom` para bloquear repetição.
  - Caso ocorra, a sala mostra apenas uma mensagem e um botão "Continuar" sem conteúdo duplicado.
- Testes em salas narrativas com bifurcações (`StoryRoom`) mostraram que as salas 2 e 3 ficavam desalinhadas visualmente:
  - O texto e os botões apareciam em posições não centralizadas.
  - Correção aplicada: reorganização do layout com `QVBoxLayout` e `addStretch()` para centralizar todos os elementos.

---

### Testes da Interface

- Garantia de centralização visual das telas narrativas e de combate.
- Ajuste dos textos narrativos com quebras de linha (`\n`) para evitar que os labels fiquem distorcidos em resoluções diferentes.
- Correção do layout em `promptForkChoice()` para manter estética igual à das outras salas.
- Verificação da responsividade dos botões, margens e espaçamentos.

---

### Testes de Finais

- A lógica de combate reconhece corretamente quando o inimigo derrotado é o chefe final (`BossRoom`).
- Exibição correta da janela de decisão com `QInputDialog`, oferecendo ao jogador dois finais alternativos:
  - Fugir e manter sua humanidade.
  - Assumir o trono sombrio como novo Lich.
- Os dois finais são tratados com mensagens diferentes e encerram o jogo adequadamente.

---

### Outros Problemas Identificados e Corrigidos

- **Desalinhamento nas salas 2 e 3**:
  - Botões de escolha surgiam fora do layout esperado.
  - Correção aplicando contêineres intermediários para agrupar texto e botões.

- **Itens sendo usados sem efeito**:
  - Detecção de uso incorreto da lógica condicional para "Lâmina da Purgação".
  - Corrigido com verificação específica no combate final.

- **Janelas duplicadas de descrição**:
  - Alguns textos apareciam duas vezes por conta de labels renderizados fora da ordem.
  - Corrigido com estruturação única dos labels em cada tipo de sala.

---

<div align="center">

[Retroceder](implementacao.md) • [Início](README.md)

</div>
