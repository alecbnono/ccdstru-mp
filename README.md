# CCDSTRU Machine Project: Discrete Structures
**Term 2, AY 2024-2025**

## Project Overview
This project is a C-based implementation of a formal system grounded in Set Theory and Relational Logic. It simulates a state-based game played on a 4x4 grid where three entities—**Uno**, **Dos**, and **Tres**—compete based on specific mathematical win conditions.

## Mathematical Foundations

### 1. The Coordinate Space
The system is defined by the following sets:
* **Set A**: $\{1, 2, 3, 4\}$, defining the coordinate range.
* **Set P**: $A \times A$, the Cartesian product representing all 16 grid positions (e.g., $(1,1)$ to $(4,4)$).
* **Set B**: Boolean values `{true, false}` used for system state flags.

### 2. The Hourglass Pattern ($W$)
The winning configurations are derived from the relationship between two specific sets:
* **Relation T**: A relation on $A$ that is reflexive, symmetric, antisymmetric, and transitive. In a 4x4 grid, this corresponds to the **Main Diagonal**: `{(1,1), (2,2), (3,3), (4,4)}`.
* **Set C**: A collection of four predefined patterns: the top row, the bottom row, the main diagonal, and the anti-diagonal.
* **Set W ($C - T$)**: By calculating the set difference between $C$ and $T$, we remove the main diagonal. The remaining patterns form an **Hourglass** shape (consisting of the top row, bottom row, and the anti-diagonal).

## System Behavior

### State Variables
* **Entity Sets**: `Uno`, `Dos`, and `Tres` (all are subsets of $P$).
* **F**: The set of remaining available moves in the coordinate space.
* **Flags**: `turn` (current player), `go` (active status), and `over` (termination status).

### Move Logic (`NextPlayerMove`)
When a move is made at a position ($pos \in P$):
1. The system checks if the move is valid based on the current `turn` and `go` status.
2. The position is added to the set of the respective player (`Uno` or `Tres`).
3. The `turn` and `go` flags are toggled to transition to the next state.

### Game Termination (`GameOver`)
The game ends when the `over` flag becomes true. The winner is determined by the following logic:

| Winner | Condition |
| :--- | :--- |
| **Uno Wins** | The coordinates in set `Uno` match a pattern in $W$. |
| **Tres Wins** | The coordinates in set `Tres` match a pattern in $W$. |
| **Dos Wins** | The set of available moves $F$ becomes empty before any other win condition. |

## Technical Implementation
* **Language**: C
* **Target Environment**: Arch Linux (Standard C libraries)
* **Logic**: Set operations are implemented using array manipulation or bitmasking to simulate formal set behavior.

## How to Run
1. **Compile**:
   ```bash
   gcc -Wall -std=c99 main.c -o main
   ```
2. **Execute**:
   ```
   ./main
   ```
