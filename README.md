# Parallel Computing & OpenMP Benchmarks (C++)

A C++ performance benchmarking suite evaluating shared-memory parallel processing capabilities using **OpenMP**. The project benchmarks single-threaded versus multi-threaded execution across array modifications, manual workload partitioning, and parallel reduction algorithms over large datasets.

## Key Features
- **Parallel Array Addition (`solveQuestion1`):** Benchmarks execution time scaling from 1 thread to 4 threads across 1,000,000 elements using `#pragma omp parallel for`.
- **Custom Workload Chunking (`solveQuestion2`):** Demonstrates manual thread ID mapping, chunk size calculation, and remainder absorption for vector scalar multiplication across threads.
- **Parallel Maximum Reduction (`solveQuestion3`):** Implements OpenMP's `reduction(max)` clause to identify peak values across 1,000,000 pseudo-random numbers without race conditions.

## Technical Concepts Covered
- **Concurrency & Multithreading:** OpenMP API (`omp_set_num_threads`, `omp_get_wtime`, `omp_get_thread_num`).
- **Parallel Design Patterns:** Work-sharing constructs, static scheduling, data reduction, and dynamic memory management in C++.
- **Benchmarking:** High-resolution wall-clock execution timing.

## Prerequisites & Compilation
Requires a C++ compiler with **OpenMP** support (GCC/G++, Clang, or MSVC).

### Compile with GCC (Linux/MinGW)
```bash
g++ -O2 -fopenmp openmp_benchmarks.cpp -o openmp_benchmarks
```
 ### Run Executable
```bash
 ./openmp_benchmarks
 ```
