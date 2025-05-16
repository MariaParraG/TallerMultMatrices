# Comparación de Algoritmos de Multiplicación de Matrices

Este proyecto implementa dos algoritmos de multiplicación de matrices:
- Algoritmo ingenuo (naive)
- Algoritmo de Strassen

Las implementaciones están hechas en **C**, **C++**, **Java** y **Python**.

---

## 📁 Archivos

| Lenguaje | Archivo              |
|----------|----------------------|
| C        | `matrix_mult.c`      |
| C++      | `matrix_mult.cpp`    |
| Java     | `MatrixMult.java`    |
| Python   | `matrix_mult.py`     |

---

## 🚀 Instrucciones de Ejecución

### 🔷 C

```bash
gcc -O3 matrix_mult.c -o matrix_mult
./matrix_mult
```

### 🔷 C++

```bash
g++ -O3 matrix_mult.cpp -o matrix_mult
./matrix_mult
```

### 🔶 Java

```bash
javac MatrixMult.java
java -server MatrixMult
```

> ⚠️ Asegúrate de usar la opción `-server` para una mejor optimización en tiempo de ejecución.

### 🟢 Python

```bash
python3 matrix_mult.py
```

> 💡 Para mejorar el rendimiento puedes usar PyPy:

```bash
pypy3 matrix_mult.py
```

---

## 📊 Resultados Esperados

Cada archivo imprimirá el tiempo de ejecución en milisegundos para:

- Multiplicación naive
- Multiplicación con Strassen

Las matrices utilizadas son de tamaño **512 × 512**, ajustable en el código.

---

## 📌 Requisitos

- GCC / G++ (con soporte para `-O3`)
- JDK 8 o superior
- Python 3.x (o PyPy)
- SO compatible (Linux / macOS / Windows)

---

## 👨‍💻 Autor

- María Ángel Parra Garzón
- Universidad Sergio Arboleda
- Taller de Arquitectura de Computadores
