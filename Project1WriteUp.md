# Project 1 Write Up
## Table for Warm-up
| Kernel | Arithmetic Intensity |
| :---   | :---:                |
| Y[j] += Y[j] + A[j][i] * B[i] | **3/32 flops/byte** (3/4 flops = 3 loads, 1 store, 3 operations) |
| s += A[i] * A[i] | **1/4 flops/byte** (2 flops = 1 load, 2 operations) |
| s += A[i] * B[i] | **1/8 flops/byte** (1 flop = 2 loads, 2 operations) |
| Y[i] = A[i] + C*B[i] | **1/12 flops/byte** (2/3 flops = 2 loads, 1 store, 2 operations) |
