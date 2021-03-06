#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <cblas.h>

#define N 2000

static struct timespec ts_start, ts_stop;

void start_timer(void)
{
  clock_gettime(CLOCK_MONOTONIC_RAW, &ts_start);
}

void stop_timer(void)
{
  clock_gettime(CLOCK_MONOTONIC_RAW, &ts_stop);
}

void print_time(void)
{
  double time =
    ((double)ts_stop.tv_sec + (double)ts_stop.tv_nsec * 1e-9) - 
    ((double)ts_start.tv_sec + (double)ts_start.tv_nsec * 1e-9);
  printf("time = %f\n", time);
}

double *alloc_matrix(int height, int width)
{
    return malloc(sizeof(double) * height * width);
}

void free_matrix(double *matrix)
{
    free(matrix);
}

void set_random_matrix(double *matrix, int height, int width)
{
    int i;
    for (i = 0; i < height * width; i++)
        matrix[i] = (double)rand() / RAND_MAX;
}

void clear_matrix(double *matrix, int height, int width)
{
    memset(matrix, 0, sizeof(double) * height * width);
}

int main(void)
{
    double *a, *b, *c;
    
    a = alloc_matrix(N, N);
    b = alloc_matrix(N, N);
    c = alloc_matrix(N, N);
    
    set_random_matrix(a, N, N);
    set_random_matrix(b, N, N);
    clear_matrix(c, N, N);
    
    start_timer();
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
        N, N, N, 1.0, a, N, b, N, 0.0, c, N);
    stop_timer();
    print_time();

    return 0;
}
