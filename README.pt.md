# 📐 number-theory-algorithms

---

## 🛠️ Como Executar Localmente

Os algoritmos são implementados em **C puro**, sem dependências externas. Para compilar e executar localmente:

### ✅ Pré-requisitos

* [GCC](https://gcc.gnu.org/) ou outro compilador C instalado
  (Em sistemas Unix/Linux/macOS, normalmente já vem instalado; no Windows, você pode usar o [MinGW](http://www.mingw.org/)).

### ▶️ Compilando e Executando um Arquivo

Navegue até a pasta desejada e execute:

```bash
gcc nome_do_arquivo.c -o programa
./programa
```

### 📦 Exemplo

```bash
cd mdc
gcc recursivo.c -o mdc_rec
./mdc_rec
```

### 📝 Observações

* Alguns códigos podem requerer entrada via `scanf`.
* Outros podem já conter valores fixos para teste.
* Sinta-se livre para modificar os arquivos para testes manuais.

---

## 📁 Estrutura do Projeto

Cada **pasta principal** representa um tópico ou problema matemático, e contém:

* **Subpastas**, quando houver múltiplas abordagens ou algoritmos mais complexos relacionados.
* **Arquivos `.c`** com diferentes implementações (recursivas, iterativas, otimizadas, etc.).

---

## 🧮 Tópicos e Planejamento

### 1. Aritmética e Divisibilidade

| Pasta       | Descrição                                 | Arquivos/Subpastas                   |
| ----------- | ----------------------------------------- | ------------------------------------ |
| `mdc`       | Algoritmo de Euclides para calcular o MDC | `recursivo.c`, `iterativo.c`         |
| `fatoracao` | Fatoração de inteiros em primos           | `divisao_tentativa/`, `pollard_rho/` |

---

### 2. Testes de Primalidade e Números Primos

| Pasta         | Descrição                                       | Arquivos/Subpastas                                  |
| ------------- | ----------------------------------------------- | --------------------------------------------------- |
| `primalidade` | Testes básicos e probabilísticos de primalidade | `divisao_tentativa.c`, `fermat.c`, `miller_rabin.c` |
| `crivo`       | Geração de primos com o Crivo de Eratóstenes    | `basico.c`, `segmentado.c`                          |
| `wilson`      | Teste de primalidade usando o Teorema de Wilson | `fatorial_modular.c`                                |

---

### 3. Congruências e Aritmética Modular

| Pasta          | Descrição                                                 | Arquivos/Subpastas                    |
| -------------- | --------------------------------------------------------- | ------------------------------------- |
| `fermat`       | Exponenciação modular usando o Pequeno Teorema de Fermat  | `exponenciacao_modular.c`             |
| `euler`        | Função totiente e Teorema de Euler                        | `totiente/`, `congruencias/`          |
| `chines_resto` | Resolução de sistemas de congruências pelo Teorema Chinês | `iterativo.c`, `inversos_modulares.c` |
| `inverso_mod`  | Cálculo de inversos modulares com Euclides Estendido      | `inverso.c`                           |

---

### 4. Números Especiais e Sequências

| Pasta       | Descrição                                   | Arquivos/Subpastas                          |
| ----------- | ------------------------------------------- | ------------------------------------------- |
| `perfeitos` | Identificação de números perfeitos          | `exaustiva.c`, `euclides_euler.c`           |
| `amigos`    | Busca de pares de números amigos            | `busca_pares.c`                             |
| `fibonacci` | Geração e análise da sequência de Fibonacci | `recursivo.c`, `iterativo.c`, `matricial.c` |

---

### 5. Aplicações Avançadas

| Pasta          | Descrição                                 | Arquivos/Subpastas        |
| -------------- | ----------------------------------------- | ------------------------- |
| `rsa`          | Implementação básica do algoritmo RSA     | `chaves/`, `encriptacao/` |
| `log_discreto` | Solução do problema do logaritmo discreto | `baby_step_giant_step.c`  |

---

## 🧾 Notas Finais

Este repositório é um **projeto em evolução**, feito por curiosidade e pelo prazer de codificar problemas matemáticos. Se você também gosta de matemática e programação, talvez encontre algo interessante por aqui.

> Para dúvidas ou sugestões, abra uma issue ou envie um PR!
> Boa codificação! 😄

---
