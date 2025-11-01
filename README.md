# ⚓ Batalha Naval com Habilidades — Desafio Nível Avançado

Projeto desenvolvido como parte do **Desafio Nível Avançado** do módulo de **Vetores e Matrizes**.  
O objetivo deste desafio é aplicar o conhecimento sobre **arrays bidimensionais** (matrizes) na criação de um tabuleiro de **Batalha Naval**, adicionando a visualização de **habilidades especiais** com diferentes áreas de efeito.

---

## 🎯 Objetivo do Projeto

O programa simula um **tabuleiro de Batalha Naval 10x10**, contendo quatro navios e três habilidades especiais:
- **Cone**
- **Cruz**
- **Octaedro**

Cada habilidade possui uma **área de efeito** representada por uma matriz, e o programa sobrepõe essas áreas sobre o tabuleiro principal, marcando visualmente as posições afetadas.

---

## 🧩 Estrutura do Programa

### 🔹 1. Tabuleiro Principal
- Representado por uma **matriz 10x10**.
- Todas as posições iniciam com o valor `0`, representando **água**.
- Navios são marcados com o valor `3`.

### 🔹 2. Navios
- Quatro navios de tamanho fixo (3 posições cada).
- Dois posicionados **horizontalmente ou verticalmente**.
- Dois posicionados **diagonalmente**.
- O programa garante que os navios:
  - Estão **dentro dos limites** do tabuleiro.
  - **Não se sobrepõem** entre si.

### 🔹 3. Habilidades Especiais
Cada habilidade é representada por uma **matriz 5x5** com valores:
- `1` → área afetada pela habilidade.
- `0` → área não afetada.

#### 🌀 Tipos de habilidades:
- **Cone:** Área expandindo de um ponto superior em direção à base.
- **Cruz:** Linhas horizontal e vertical cruzando o ponto central.
- **Octaedro (Losango):** Formato de losango, com o centro como ponto de origem.

As posições afetadas são marcadas no tabuleiro com o valor **`5`**.

---

## 🖥️ Exemplo de Saída

### Tabuleiro com Habilidade (Cruz)
