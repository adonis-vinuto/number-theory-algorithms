# 📐 number-theory-algorithms

---

## 🛠️ How to Run Locally

The algorithms are implemented in **pure C**, with no external dependencies. To compile and run locally:

### ✅ Prerequisites

* [GCC](https://gcc.gnu.org/) or another C compiler installed
  (On Unix/Linux/macOS systems, it usually comes pre-installed; on Windows, you can use [MinGW](http://www.mingw.org/)).

### ▶️ Compiling and Running a File

Navigate to the desired folder and run:

```bash
gcc filename.c -o program
./program
```

### 📦 Example

```bash
cd mdc
gcc recursivo.c -o gcd_rec
./gcd_rec
```

### 📝 Notes

* Some programs may require input via `scanf`.
* Others may have hardcoded values for testing purposes.
* Feel free to modify the files for manual tests.

---

## 📁 Project Structure

Each **main folder** represents a mathematical topic or problem and contains:

* **Subfolders**, when there are multiple approaches or more complex related algorithms.
* `.c` **files** with different implementations (recursive, iterative, optimized, etc.).

---

## 🧮 Topics and Planning

### 1. Arithmetic and Divisibility

| Folder      | Description                        | Files/Subfolders                     |
| ----------- | ---------------------------------- | ------------------------------------ |
| `mdc`       | Euclidean Algorithm to compute GCD | `recursivo.c`, `iterativo.c`         |
| `fatoracao` | Integer factorization into primes  | `divisao_tentativa/`, `pollard_rho/` |

---

### 2. Primality Testing and Prime Numbers

| Folder        | Description                                      | Files/Subfolders                                    |
| ------------- | ------------------------------------------------ | --------------------------------------------------- |
| `primalidade` | Basic and probabilistic primality tests          | `divisao_tentativa.c`, `fermat.c`, `miller_rabin.c` |
| `crivo`       | Prime generation using the Sieve of Eratosthenes | `basico.c`, `segmentado.c`                          |
| `wilson`      | Primality testing via Wilson’s Theorem           | `fatorial_modular.c`                                |

---

### 3. Congruences and Modular Arithmetic

| Folder         | Description                                                  | Files/Subfolders                      |
| -------------- | ------------------------------------------------------------ | ------------------------------------- |
| `fermat`       | Modular exponentiation using Fermat's Little Theorem         | `exponenciacao_modular.c`             |
| `euler`        | Totient function and Euler’s Theorem                         | `totiente/`, `congruencias/`          |
| `chines_resto` | Solving systems of congruences via Chinese Remainder Theorem | `iterativo.c`, `inversos_modulares.c` |
| `inverso_mod`  | Modular inverse using Extended Euclidean Algorithm           | `inverso.c`                           |

---

### 4. Special Numbers and Sequences

| Folder      | Description                                   | Files/Subfolders                            |
| ----------- | --------------------------------------------- | ------------------------------------------- |
| `perfeitos` | Identification of perfect numbers             | `exaustiva.c`, `euclides_euler.c`           |
| `amigos`    | Search for pairs of amicable numbers          | `busca_pares.c`                             |
| `fibonacci` | Generation and analysis of Fibonacci sequence | `recursivo.c`, `iterativo.c`, `matricial.c` |

---

### 5. Advanced Applications

| Folder         | Description                            | Files/Subfolders          |
| -------------- | -------------------------------------- | ------------------------- |
| `rsa`          | Basic implementation of RSA algorithm  | `chaves/`, `encriptacao/` |
| `log_discreto` | Solving the discrete logarithm problem | `baby_step_giant_step.c`  |

---

## 🧾 Final Notes

This repository is a **work in progress**, created out of curiosity and a passion for coding math problems. If you also enjoy math and programming, you might find something useful or fun here.

> For questions or suggestions, feel free to open an issue or send a PR!
> Happy coding! 😄