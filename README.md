# Algoritmos em C

Repositório dedicado ao estudo e desenvolvimento de algoritmos, estruturas de controle e desafios práticos na linguagem C.

---

## 📁 Projetos e Desafios

### 1. A Compra da Empilhadeira (`Empilhadeira.c`)
- **Cenário:** Simulação financeira da quitação da dívida de uma empilhadeira da empresa fictícia FerraLog.
- **Conceitos aplicados:**
  - Entrada de dados com validação (`scanf`).
  - Verificação preventiva com `if` para barrar operações onde a parcela mensal não cobre os juros do primeiro mês (evitando loops infinitos e dívida impagável).
  - Laço de repetição `while` para calcular o número de meses necessários para amortização total.

### 2. O Termostato do Servidor (`Termostato.c`)
- **Cenário:** Sistema de monitoramento térmico para a sala de servidores durante um turno de 8 horas após pane no ar-condicionado principal.
- **Conceitos aplicados:**
  - Laço de repetição `for` simulando as 8 horas de trabalho.
  - Regras condicionais sequenciais para aquecimento e acionamento do ar de emergência (-5°C caso atinja >= 28°C).
  - Uso de `break` para parada crítica imediata caso a temperatura atinja o limite de segurança (35°C).

---

## 🛠️ Como Compilar e Executar

Certifique-se de ter o compilador **GCC** instalado em seu sistema.

### Compilando os programas

```bash
# Compilar o programa da Empilhadeira
gcc Empilhadeira.c -o Empilhadeira

# Compilar o programa do Termostato
gcc Termostato.c -o Termostato
```

### Executando

```bash
# Executar a Empilhadeira
./Empilhadeira

# Executar o Termostato
./Termostato
```
