# Process-Control-Block-PCB-Management-Simulation-in-C
Two C implementations simulating process creation and destruction using different PCB structures: one with linked lists, another with sibling pointers. Benchmarks included.

# PCB Management Simulation in C

## Overview
This project demonstrates two different approaches to implementing process hierarchies using Process Control Blocks (PCBs) in C. Each file uses a different data structure to simulate process creation, deletion, and traversal. Both versions benchmark execution time for performance comparison.

## Files

### `pcb1.c`
- Uses dynamically allocated linked lists to track child processes.
- Each PCB stores a pointer to its list of children.
- Functions:
  - `initialize()` — Initializes the PCB table.
  - `create(p)` — Creates a child process for parent `p`.
  - `destroy(p)` — Recursively destroys all descendants of `p`.
  - `printList(p)` — Prints all children of process `p`.

### `pcb2.c`
- Uses static memory and simulates a tree using `first child`, `younger sibling`, and `older sibling` fields.
- Avoids dynamic memory allocation.
- Functions:
  - `initialize()` — Initializes the PCB table.
  - `create(p)` — Adds a child process to parent `p` using sibling pointers.
  - `destroy(p)` — Recursively deletes `p` and its subtree while maintaining sibling pointers.
  - `printList(p)` — Prints all children of process `p`.

## Timing
Both implementations use `GET_TIME()` from `timer.h` to measure the elapsed time for execution.

## Usage
Compile using:
```bash
gcc pcb1.c -o pcb1
./pcb1
