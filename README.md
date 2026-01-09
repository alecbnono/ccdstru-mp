# CCDSTRU Machine Project - Discrete Structures
**Term 2, AY 2024-2025**

## Project Overview
[cite_start]This project is a C-language implementation of a formal system defined by set theory and relational logic[cite: 8]. [cite_start]The system models state-based interactions between three entities (**Uno**, **Dos**, and **Tres**) within a coordinate space[cite: 16, 43].

## Mathematical Specifications

### 1. Universal Sets
The system is built upon the following mathematical foundations:
* [cite_start]**Set A**: $\{x \in \mathbb{Z}^{+} \mid x < 5\}$, which defines the coordinate range $\{1, 2, 3, 4\}$[cite: 10].
* [cite_start]**Set P**: The Cartesian product $A \times A$, representing a 4x4 coordinate grid[cite: 11].
* [cite_start]**Set B**: Boolean values {true, false} used for system state flags[cite: 12].
* [cite_start]**Set C**: A collection of specific winning coordinate patterns[cite: 13].

### 2. Relations and Winning Conditions
* [cite_start]**Relation T**: A relation on $A$ that is simultaneously reflexive, symmetric, antisymmetric, and transitive (the identity relation)[cite: 14].
* [cite_start]**Set W**: Defined by the set difference $W = C - T$, representing the valid winning configurations for the system[cite: 20].

## System Components

### System Variables
The program tracks the following variables to maintain the game state:
* [cite_start]**Subsets of P**: `Uno`, `Dos`, `Tres`, and `F` (representing player moves and available spaces)[cite: 16].
* [cite_start]**State Flags**: `turn` (current player), `go` (active status), and `over` (termination status)[cite: 17, 23].

### Initialization
At the start of the program, the system state is defined as follows:
* [cite_start]`Uno`, `Dos`, and `Tres` are initialized as empty sets ($\emptyset$)[cite: 24, 25, 26].
* [cite_start]`go` and `over` are initialized as Boolean values[cite: 23].

## Logic and Behavior

### NextPlayerMove(pos)
When a move is made at a position ($pos \in P$), the system updates based on the following logic:
* [cite_start]**Turn Management**: The `turn` variable alternates between players ($\neg turn$)[cite: 36].
* [cite_start]**Set Updates**: Depending on the state of `turn` and `go`, the position is added to either set `Uno` or set `Tres`[cite: 35, 41].
* [cite_start]**Toggle State**: The `go` flag is flipped ($\neg go$) to signal the next phase of the move[cite: 37, 42].

### GameOver Condition
[cite_start]The game terminates (`over` becomes true) under three specific conditions[cite: 21]:
1. [cite_start]**Uno Wins**: If the set of positions in `Uno` matches a pattern in `W`[cite: 44, 49].
2. [cite_start]**Tres Wins**: If the set of positions in `Tres` matches a pattern in `W`[cite: 46, 51].
3. [cite_start]**Dos Wins**: If the set of available positions `F` becomes empty ($\emptyset$) before a winner is declared[cite: 45, 50].

## Implementation Details
* [cite_start]**Language**: C [cite: 8]
* [cite_start]**Deadline**: April 1, 2025, 08:00 [cite: 7]
* [cite_start]**Department**: Software Technology, College of Computer Studies [cite: 3, 5]
