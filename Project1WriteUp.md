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

     By definition, the peak perforance is the multiplication of clock speed, number of cores, and the number of independent FPUs (1 for this example).

    | Computer            | MFlops/s (avg over 3 trials) | Processor Clock Speed (GHz) | L1 cache size | L2 cache size | L3 cache size | Number of cores | Peak Performance (Gflops/s) |
    |---------------------|------------------------------|-----------------------------|---------------|---------------|---------------|-----------------|-----------------------------|
    | Jared's Desktop     |            994.67            |             5.8             |      2.1 MB   |     32.0 MB   |      36.0 MB  |       24        |              139.2          |
    | HPCC (dev-indel18)  |                              |             2.4             |      32 KB    |     1024 KB   |     28160 KB  |       20        |               48.0          |
    


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

    On Berk's laptop:
        Trial 1: 407.036204 Mflops/s
        Trial 2: 437.458782 Mflops/s
        Trial 3: 453.406243 Mflops/s

4. For the system you are running on, determine the clock speed of the processor and the cache size/layout. Use this information to estimate the theoretical peak performance of the system, assuming that the processor is capable of one flop per clock cycle (generally NOT true on modern architectures). How does the performance you measured in (3) compare to the theoretical peak performance of your system?
    On Jared's lab computer: (<https://www.intel.com/content/www/us/en/gaming/resources/cpu-clock-speed.html>)
        - 5.8 GHz processor
        - L1 cache: 2.1 MB
        - L2 cache: 32.0 MB
        - L3 cache: 36.0 MB
    By definition, the peak perforance is the multiplication of clock speed, number of cores, and the number of independent FPUs.
    Peak performance = 24 cores _5.8 GHz_ 1 (FPUs per core)  = 185.136 GFlops = 185136 Mflops/s

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

    On Berk's laptop:
        - 3.2 GHz processor
        - L1 cache: 2.9 MB
        - L2 cache: 28 MB
        - L3 cache: 24 MB
    Peak performance = 8 performance cores _3.2 GHz_ + 2 efficiency cores _2.02_ 1 FPU = 29.64 GFlops/s = 5600 Mflops/s

5. Now repeat the performance measurement for a range of matrix size `N` from 1 to 10,000,000. Make a plot of the resulting measured Gflop/s vs. `N`. On this plot place a horizontal line representing the theoretical peak performance based upon your system's clock speed.

6. How does the measured performance for multiple _N_'s compare to peak? Are there any "features" in your plot? Explain them in the context of the hardware architecture of your system. Include in your write-up a description of your system's architecture (processor, cache, etc.).

    #TODO: Finish this problem

To your project git repo, commit your code for performing the matrix-matrix multiply performance measurements, the plots of your results, and a brief write-up (in plain text or markdown) addressing the above questions and discussing your results. Pay particular attention to the comparison between different architectures and give explanations for them.

## Part 2: The Roofline Model

3. Run the ERT in serial mode on your local machine. Report the peak performances and bandwidths (for all caches levels as well as DRAM). Where is the "ridge point" of the roofline for the various cases?
    In response below, obtained by running on the HPCC (See roofline.png)

4. Consider the four FP kernels in "Roofline: An Insightful Visual Performance Model for Floating-Point Programs and Multicore Architectures" (see their Table 2). Assuming the high end of operational (i.e., "arithmetic") intensity, how would these kernels perform on the platforms you are testing? What optimization strategy would you recommend to increase performance of these kernels?

    Information for answers to this question were found in <https://crd.lbl.gov/assets/pubs_presos/parlab08-roofline-talk.pdf>.

    SpMV: Relatively low arithmetic intensity. It will be memory bound, so it won't reach the peak performance. Nowhere to utilize locality, so it requires a lot of memory loading. An optimization strategy that we would recommend would be matrix compression with register blocking, as that would improve the flop:byte ratio of this kernel.

    LBMHD: An optimization strategy that we would recommend is explicit SIMDization and cache bypass using the instruction movntpd, as this will increase the flop:byte ratio to ~1.0 on x86/Cell (compared to 0.7 flop:byte without).

    Stencil: Jacobi method, must read every point from DRAM, perform 8 flops, and then write every point back to DRAM. Cache locality is the most important factor when it comes to performance of the Stencil kernel. Performs at just over 0.5 flops/byte ideally, which is achieved by optimizing using SIMDization and cache bypass. However, Stencil can also be optimized to a 1/3 flop:byte ratio using cache blocking.

    3-D FFT: #TODO: Finish this problem

5. Address the same questions in (4) for the four kernels given in the Warm-up above.

    #TODO Finish this problem

6. Compare your results for the roofline model to what you obtained for the matrix-matrix multiplication operation from Part 1. How are the rooflines of memory bandwidth related to the features in the algorithmic performance as a function of matrix size?
    #TODO Finish this problem

To your project write-up, add your plots of the roofline model for the systems you tested, and responses addressing the above questions.
