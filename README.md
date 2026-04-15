# AlgGen2025

This project was created as part of the course "Foundations of Object-Oriented Programming." It implements a simple evolutionary optimization algorithm in C++ using classes that represent candidates, populations, and the algorithm controller.

## Project goal

The goal of this project is to demonstrate the practical use of object-oriented programming in C++ to implement a population-based optimization algorithm. The project illustrates:

- class design and data encapsulation,
- object cooperation in a genetic algorithm model,
- basic evolutionary mechanisms: population creation, evaluation, selection, crossover, and mutation.

## Project structure

- `Main.cpp` - program entry point; initializes and runs the algorithm.
- `TAlgorithm.h` / `TAlgorithm.cpp` - class that manages the optimization process and controls the algorithm loop.
- `TPopulation.h` / `TPopulation.cpp` - class representing a population of candidates and population operations.
- `TCandidate.h` / `TCandidate.cpp` - class representing an individual candidate (solution) with evaluation.
- `TParam.h` / `TParam.cpp` - class representing a genetic parameter, storing range, step size, and bit conversion.

## How to run

The project can be compiled with any C++ compiler supporting C++11 or newer.

Example compilation command:

```bash
g++ -std=c++11 Main.cpp TAlgorithm.cpp TPopulation.cpp TCandidate.cpp TParam.cpp -o AlgGen2025
```

Then run:

```bash
./AlgGen2025
```

> In `Main.cpp`, you can change the `TAlgorithm` constructor arguments to adjust the number of candidates, maximum number of populations, and minimum improvement threshold.

## How it works

The program creates an instance of `TAlgorithm`, which manages the cycle of the evolutionary algorithm. The main steps are:

1. Create the initial population of candidates.
2. Evaluate and select the best candidates.
3. Perform crossover and mutation on selected solutions.
4. Check stop conditions such as population count and minimum improvement.
5. Keep track of the best solution found during the run.

## Main classes

- `TAlgorithm`
  - manages successive populations,
  - monitors progress and stop conditions,
  - tracks the best solutions.

- `TPopulation`
  - represents a group of candidates,
  - creates sample data,
  - computes population evaluation,
  - performs crossover and mutation.

- `TCandidate`
  - stores genes and solution evaluation,
  - supports conversion to/from bitstring format,
  - evaluates candidate quality.

- `TParam`
  - stores the possible range of a parameter,
  - converts a value to a bitstring and back,
  - supports random parameter assignment.

## Notes

- This project is an educational example and does not include advanced multithreading or a graphical interface.
- The project can be extended with additional evaluation criteria, result logging, or visualization of the algorithm progress.

## Author

This project was prepared as part of the course `Foundations of Object-Oriented Programming`.
