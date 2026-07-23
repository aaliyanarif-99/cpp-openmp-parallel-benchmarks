#include <iostream>
#include <random>
#include <omp.h>
using namespace std;

void solveQuestion1() {
    const int SIZE = 1000000;
    int uniqueInput = 2; 

    double *data = new double[SIZE];
    for (int i = 0; i < SIZE; i++) data[i] = i;

    cout << "Processors available: " << omp_get_num_procs() << endl;

    // Single-thread run
    omp_set_num_threads(1);
    double t0 = omp_get_wtime();
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < SIZE; i++) {
        data[i] += uniqueInput;
    }
    double t1 = omp_get_wtime();
    cout << "[Q1] Time (1 thread): " << (t1 - t0) << " sec" << endl;

    for (int i = 0; i < SIZE; i++) data[i] = i; // reset before second run

    // Four-thread run
    omp_set_num_threads(4);
    double t2 = omp_get_wtime();
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < SIZE; i++) {
        data[i] += uniqueInput;
    }
    double t3 = omp_get_wtime();
    cout << "[Q1] Time (4 threads): " << (t3 - t2) << " sec" << endl;

    delete[] data;
}

void solveQuestion2() {
    const int SIZE = 500000;
    int scalarValue = 2; 

    double *vec = new double[SIZE];
    for (int i = 0; i < SIZE; i++) vec[i] = i;

    double t0 = omp_get_wtime();
    #pragma omp parallel num_threads(2)
    {
        int id = omp_get_thread_num();
        int nthreads = omp_get_num_threads();
        int chunk = SIZE / nthreads;
        int start = id * chunk;
        int end = (id == nthreads - 1) ? SIZE : start + chunk; // last thread absorbs remainder

        for (int i = start; i < end; i++) {
            vec[i] = vec[i] * scalarValue;
        }
    }
    double t1 = omp_get_wtime();

    cout << "[Q2] Total execution time: " << (t1 - t0) << " sec" << endl;
    cout << "[Q2] Last element vec[N-1] = " << vec[SIZE - 1] << endl;

    delete[] vec;
}

void solveQuestion3() {
    const int SIZE = 1000000;
    long plantedValue = 12004; 

    long *values = new long[SIZE];
    mt19937 rng(2026); // fixed seed for reproducibility
    uniform_int_distribution<int> dist(0, 9999);
    for (int i = 0; i < SIZE; i++) values[i] = dist(rng);
    values[SIZE / 2] = plantedValue; // planted AFTER the fill completes

    long localMax = values[0];
    omp_set_num_threads(4);
    double t0 = omp_get_wtime();
    #pragma omp parallel for reduction(max:localMax)
    for (int i = 0; i < SIZE; i++) {
        if (values[i] > localMax) localMax = values[i];
    }
    double t1 = omp_get_wtime();

    cout << "[Q3] Execution time: " << (t1 - t0) << " sec" << endl;
    cout << "[Q3] Maximum value: " << localMax << endl;

    delete[] values;
}

int main() {
    cout << "===== Question 1: Array Addition =====" << endl;
    solveQuestion1();

    cout << "\n===== Question 2: Vector Multiplication =====" << endl;
    solveQuestion2();

    cout << "\n===== Question 3: Find Maximum Value =====" << endl;
    solveQuestion3();

    return 0;
}
