# Algoritmos em C

Repositório dedicado ao estudo e desenvolvimento de algoritmos, estruturas de controle e desafios práticos na linguagem C.

---

## 📁 Estrutura do Repositório

### 1. `Atividades/`
Exercícios práticos iniciais de simulação e controle:
- **`Empilhadeira.c`:** Simulação financeira da quitação da dívida de uma empilhadeira com cálculo de amortização e juros mensais via `while`.
- **`Termostato.c`:** Monitoramento térmico de sala de servidores em turno de 8 horas com controle de ar de emergência via `for`.

### 2. `FerraLog/`
Evolução do sistema de inventário e logística FerraLog:
- **`ferralog/ferralog.c`:** Sistema completo integrado com cadastro de ferramentas, leitura de QR Code, verificação de garantias, relatórios de risco financeiro e menu interativo.
- **Módulos e protótipos de aula:**
  - `menu.c`: Estrutura visual do menu principal.
  - `sleep.c`: Efeitos de carregamento de sistema com pausas temporizadas.
  - `switch-case-ferralog.c`: Navegação e despacho de opções via `switch/case`.
  - `desafio-ferralog-com-if.c`: Validações de entrada e alertas com `if/else`.
  - `desafio-ferralog-com-while.c`: Loop contínuo de sessão com `do-while`.

### 3. `Atividade_Desafio/`
Lista com 10 desafios práticos de lógica e algoritmos:
- **`q01_eleitores.c`:** Percentual de votos brancos, nulos e válidos em relação ao total de eleitores.
- **`q02_divisao.c`:** Divisão de dois valores com repetição obrigatória enquanto o segundo valor for zero.
- **`q03_serie.c`:** Cálculo da soma da série $S = 1 + 3/2 + 5/3 + \dots + 99/50$.
- **`q04_busca_nome.c`:** Leitura de 10 nomes em vetor e busca linear com resposta `ACHEI` ou `NAO ACHEI`.
- **`q05_media_turma.c`:** Armazenamento de 20 notas, cálculo da média e contagem de alunos acima dela.
- **`q06_plano_saude.c`:** Cálculo de mensalidade por faixa etária com acréscimo proporcional por doenças crônicas.
- **`q07_soma_n.c`:** Soma dos $N$ números consecutivos a partir de $A$ (com validação para $N > 0$).
- **`q08_primos.c`:** Identificação e listagem de números primos em um vetor de 20 inteiros positivos.
- **`q09_vogais.c`:** Função dedicada para leitura de mensagem e contagem individual das vogais (A, E, I, O, U).
- **`q10_sem_vogais.c`:** Filtragem de string removendo todas as vogais informadas pelo usuário.

### 4. `Atividade_Entrega/`
Jogo completo para terminal com temática regional nordestina:
- **`Sertao_trail.c`:** *Sertão Trail: A Marcha dos Retirantes* — Jogo de simulação e sobrevivência na caatinga durante a Grande Seca de 1877. Integra simulação de temperatura e clima (estilo `Termostato.c`), gestão de recursos, animais e alforje com structs (estilo `ferralog.c`), economia de réis e juros/desgaste (estilo `Empilhadeira.c`), feiras livres (Teixeira, Patos, Campina Grande), eventos de cangaço e desfechos em literatura de cordel.

---

## 🛠️ Como Compilar e Executar

Certifique-se de ter o compilador **GCC** instalado.

### Exemplos de compilação:

```bash
# Compilar atividade
gcc -Wall -Wextra Atividades/Empilhadeira.c -o Empilhadeira

# Compilar o sistema FerraLog completo
gcc -Wall -Wextra FerraLog/ferralog/ferralog.c -o ferralog

# Compilar uma questão dos desafios (ex.: Questão 1)
gcc -Wall -Wextra Atividade_Desafio/q01_eleitores.c -o q01

# Compilar o jogo Sertão Trail
gcc -Wall -Wextra Atividade_Entrega/Sertao_trail.c -o sertao_trail
```

### Executando:

```bash
./Empilhadeira
./ferralog
./q01
./sertao_trail
```
