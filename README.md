

---

## 1 ESTRUTURAS DE DADOS

### 1.1 Lista Encadeada

A cobra foi implementada por meio de uma lista encadeada circular:

* Cada nó representa um segmento da cobra
* Permite crescimento dinâmico
* Evita realocação de memória contínua

**Vantagens:**

* Inserção da cabeça
* Flexibilidade no crescimento

**Desvantagem:**

* Remoção da cauda

### 1.2 Vetor de Frutas

As frutas são armazenadas em um vetor de tamanho fixo

* Acesso direto
* Quantidade constante

---

## 2. ORGANIZAÇÃO DO SISTEMA

O sistema foi dividido em módulos funcionais:

### 2.1 Menu

* Exibição do menu principal
* Seleção de modo de jogo

### 2.2 Loop Principal

O jogo opera em um loop contínuo contendo:

* Captura de entrada do usuário
* Atualização do estado do jogo
* Renderização
* Controle de tempo

### 2.3 Atualização do Jogo

Responsável por:

* Movimentação da cobra
* Verificação de colisões
* Consumo de frutas
* Atualização da pontuação

### 2.4 Sistema de Níveis

O jogo aumenta a dificuldade dinamicamente:

* Expansão do mapa
* Ajuste de velocidade

### 2.5 Tela de Game Over

Permite ao usuário:

* Reiniciar o jogo
* Retornar ao menu
* Encerrar o programa

---

## 3. ANÁLISE

### 3.1 Variáveis

* W: largura do mapa
* H: altura do mapa
* S: tamanho da cobra
* F: quantidade de frutas

### 3.2 Principais Funções

#### Atualização do Jogo (update)

#### Verificação de Colisão

#### Geração de Frutas

#### Renderização do Mapa

#### Atualização de Nível
---

## 4. PONTOS CRÍTICOS

### 4.1 Remoção da Cauda

### 4.2 Verificação de Colisão

### 4.3 Geração de Frutas

Pode exigir múltiplas tentativas para evitar sobreposição com a cobra.

---

## 5. POSSÍVEIS MELHORIAS

* Uso de matriz de ocupação para reduzir colisão para O(1)
* Implementação de lista duplamente encadeada
* Otimização do algoritmo de geração de frutas

---

## 8. FUNCIONALIDADES DO SISTEMA

O sistema desenvolvido é capaz de:

* Movimentar a cobra
* Detectar colisões com paredes
* Detectar colisões com o próprio corpo
* Gerenciar frutas
* Atualizar pontuação
* Controlar níveis de dificuldade
* Exibir interface gráfica no console
* Gerenciar fluxo de jogo (menu, jogo, game over)

---
