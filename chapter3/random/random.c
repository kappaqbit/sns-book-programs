#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <SFMT.h>

#define N ( 4000 )
#define N_E ( 3200 )
#define N_I ( ( N ) - ( N_E ) )

#define T ( 1000 )
#define DT ( 1. )
#define NT ( 1000 )

#define TAU_M ( 20. )
#define TAU_E ( 5. )
#define TAU_I ( 10. )

#define V_REST ( -49. )
#define V_INIT ( -60. )
#define V_RESET ( -60. )
#define THETA ( -50. )

#define G_E ( 1.62 / ( TAU_E ) )
#define G_I ( -9. / ( TAU_I ) )
#define P ( 0.02 )

typedef struct {
    float *v, *ge, *gi, *w;
    bool *s;
    sfmt_t rng;
    FILE *file;
} network_t;

extern void timer_start(void);
extern double timer_elapsed(void);

void initialize(network_t *n) {
    *n = (network_t) {
        .v = calloc(N, sizeof(float)),
        .ge = calloc(N, sizeof(float)),
        .gi = calloc(N, sizeof(float)),
        .w = calloc(N*N, sizeof(float)),
        .s = calloc(N, sizeof(bool)),
        .file = fopen("spike.dat", "w"),
    };

    sfmt_init_gen_rand(&n -> rng, 23);

    for (int32_t i = 0; i < N; i++) {
        n -> v[i] = V_INIT + 10. * sfmt_genrand_real2(&n -> rng);
    }

    for (int32_t i = 0; i < N; i++) {
        for (int32_t j = 0; j < N; j++) {
            n -> w[j + N * i] = (sfmt_genrand_real2(&n -> rng) < P) ? 1. : 0.;
        }
    }
}

void finalize(network_t *n) {
    free(n -> v);
    free(n -> ge);
    free(n -> gi);
    free(n -> w);
    free(n -> s);
    free(n -> file);
}

void calculateSynapticInputs(network_t *n) {
    for (int32_t i = 0; i < N; i++) {
        //exc, inh count
        float re = 0, ri = 0;
        for (int32_t j = 0; j < N; j++) {
            float r = n -> w[j + N * i] * n -> s[j];
            if (j < N_E) { re += r; } else { ri += r; }
        }
        n -> ge[i] = exp(-DT / TAU_E) * n -> ge[i] + re;
        n -> gi[i] = exp(-DT / TAU_I) * n -> gi[i] + ri;
    }
}

void updateCellParameters(network_t *n) {
    for (int32_t i = 0; i < N; i++) {
        n -> v[i] += DT * (-(n -> v[i] - V_REST) + G_E * n -> ge[i] + G_I * n -> gi[i]) /TAU_M;
        n -> s[i] = (n -> v[i] > THETA);
        n -> v[i] = (n -> s[i]) * V_RESET + (!n -> s[i]) * n -> v[i];
    }
}

void outputSpike(const int32_t nt, network_t *n) {
    for (int32_t i = 0; i < N; i++) {
        if (n -> s[i]) { fprintf(n ->file, "%f %d\n", DT * (nt + 1), i); }
    }
}

void loop (network_t *n) {
    timer_start();

    for (int32_t nt = 0; nt < NT; nt++) {
        calculateSynapticInputs(n);
        updateCellParameters(n);
        outputSpike(nt, n);
    }

    double elapsedTime = timer_elapsed();
    printf("Elapsed time = %f sec.\n", elapsedTime);
}

int main(void) {
    network_t n;

    initialize(&n);
    loop(&n);
    finalize(&n);
}
