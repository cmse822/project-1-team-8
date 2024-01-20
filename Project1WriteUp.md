# Project 1 Write Up

## Table for Warm-up

| Kernel | Arithmetic Intensity |
| :---   | :---:                |
| Y[j] += Y[j] + A[j][i] * B[i] | **3/32 flops/byte** (3/4 flops = 3 loads, 1 store, 3 operations) |
| s += A[i] * A[i] | **1/4 flops/byte** (2 flops = 1 load, 2 operations) |
| s += A[i] * B[i] | **1/8 flops/byte** (1 flop = 2 loads, 2 operations) |
| Y[i] = A[i] + C*B[i] | **1/12 flops/byte** (2/3 flops = 2 loads, 1 store, 2 operations) |

## Part 1: Matrix-matrix Multiplication

In this first part of the project, you will test the performance of the basic matrix-matrix multiplication operation as a function of matrix size on multiple compute platforms. Complete the following using at least two different compute architectures (e.g., your laptop and HPCC, or two different node architectures on HPCC).

1. With your group, write a program that multiplies two matrices together (see: <http://mathworld.wolfram.com/MatrixMultiplication.html>). Use GitHub to manage the code development and version history.
    Done!

2. For a given matrix size _N_, what is the total number of floating point operations performed by this operator?
    For two matrices of size N, the total number of operations that occurs is roughly 2N^3 - N^2. In the statement matrix_c[idx][idy] += matrix_a[idx][idz] _matrix_b[idz][idy], there are N multiplications and N-1 additions for each element in matrix_c. The resulting matrix_c has N^2 total elements. Therefore, there are N^2_ (N + (N-1)) total flops. Therefore, there are 2N^3 - N^2 total flops for matrix multiplication.

3. Using the supplied C routine `get_walltime.c`, or any other accurate means of measuring time, compute the performance in Mflop/s of the matrix-matrix multiply for _N_=100\. Be sure to perform enough repeat calculations of the timing to overcome any statistical noise in the measurement.
   
    On Jared's lab computer:
        Trial 1: 995.000000 Mflops/s
        Trial 2: 991.035857 Mflops/s
        Trial 3: 998.995984 Mflops/s

    On Jared's laptop:
        Trial 1: 249.342188 Mflops/s
        Trial 2: 380.424393 MFlops/s
        Trial 3: 127.360000 MFlops/s

    On Jacob's laptop:
        Trial 1: 577.481138 Mflops/s
        Trial 2: 612.873422 Mflops/s
        Trial 3: 557.266872 Mflops/s

5. For the system you are running on, determine the clock speed of the processor and the cache size/layout. Use this information to estimate the theoretical peak performance of the system, assuming that the processor is capable of one flop per clock cycle (generally NOT true on modern architectures). How does the performance you measured in (3) compare to the theoretical peak performance of your system?
    On Jared's lab computer: (<https://www.intel.com/content/www/us/en/gaming/resources/cpu-clock-speed.html>)
        - 5.8 GHz processor
        - L1 cache: 2.1 MB
        - L2 cache: 32.0 MB
        - L3 cache: 36.0 MB
    By definition, the peak perforance is the multiplication of clock speed, number of cores, and the number of independent FPUs.
    Peak performance = 24 cores _5.8 GHz_ 1.33 (FPUs per core)  = 185.136 GFlops = 185136 Mflops/s

    On Jared's laptop:
        - 2.6 GHz processor
        - L1 cache: 384 KB
        - L2 cache: 1.5 MB
        - L3 cache 12 MB
    Peak performance = 6 cores _2.6 GHz_ 1 FPU = 15.6 GFlops/s = 15600 Mflops/s

    On Jacob's laptop:
        - 1.4 GHz processor
        - L1 cache: 32 KB
        - L2 cache: 256 KB
        - L3 cache: 6 MB
    Peak performance = 4 cores _1.4 GHz_ 1 FPU = 5.6 GFlops/s = 5600 Mflops/s

7. Now repeat the performance measurement for a range of matrix size `N` from 1 to 10,000,000. Make a plot of the resulting measured Gflop/s vs. `N`. On this plot place a horizontal line representing the theoretical peak performance based upon your system's clock speed.

8. How does the measured performance for multiple _N_'s compare to peak? Are there any "features" in your plot? Explain them in the context of the hardware architecture of your system. Include in your write-up a description of your system's architecture (processor, cache, etc.).

To your project git repo, commit your code for performing the matrix-matrix multiply performance measurements, the plots of your results, and a brief write-up (in plain text or markdown) addressing the above questions and discussing your results. Pay particular attention to the comparison between different architectures and give explanations for them.
