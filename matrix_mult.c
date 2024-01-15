#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

static int rrand(float value)
{
    return ((float)value * (rand() / (RAND_MAX + 1.0)));
}

static float** randomize(int size)
{
    // TODO: Fix pointers to create randomized matrices.
    float arr[size][size];

    for (int idx = 0; idx < size; idx++)
    {
        for (int idy = 0; idy < size; idy++) 
        { 
            arr[idx][idy] = idx;
        }
    }

    for (int idx = size; idx > 1; idx--)
    {
        for (int idy = size; idy > 1; idy--)
        {
            int num = rrand(idx);
            int tmp = arr[idx - 1][idy - 1];

            arr[idx - 1][idy - 1] = arr[num][num];
            arr[num][num] = tmp;
        }
    }

    return arr;
}

int main()
{
    int n = 1;
    float c[n][n] = randomize(n);
    float a[n][n] = randomize(n);
    float b[n][n] = randomize(n);
    // TODO: Check if the matrices updated.

    // TODO: Add timers for the performance meajurements
    for (int idx = 0; idx < n; idx++)
    {
        for (int idy = 0; idy < n; idy++)
        {
            for (int idz = 0; idz < n; idz++)
            {
                // TODO: Make sure c is updated accordingly.
                c[idx][idy] += a[idx][idz] * b[idz][idy];
            }
        }
    }

    return 0;
}