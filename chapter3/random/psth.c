#include <stdio.h>
#include <stdlib.h>

#define N 4000 // neurons
#define T 1000 // steps
#define B 10 // bin for psth

int main(void) {
    int bins = T / B + 1;
    double *h = (double *)calloc(bins, sizeof(double));
    if (h == NULL) {
        fprintf(stderr, "memory allocation failed\n");
        return 1;
    }

    FILE *fp = fopen("spike.dat", "r");
    if (fp == NULL) {
        fprintf(stderr, "cannot open spike.dat\n");
        free(h);
        return 1;
    }

    int n;
    double t;
    while (fscanf(fp, "%lf %d", &t, &n) == 2) {
        int bin = t / B;
        if (0 <= bin && bin < bins) {
            h[bin] += 1.0;
        }
    }
    fclose(fp);

    FILE *out = fopen("popavg.dat", "w");
    if (out == NULL) {
        fprintf(stderr, "cannot open popavg.dat\n");
        free(h);
        return 1;
    }

    for (int i = 0; i < bins; i++) {
        double rate_hz = 1000.0 * h[i] / (double)(B * N);
        fprintf(out, "%d %f\n", i * B, rate_hz);
    }
    fclose(out);

    free(h);
    return 0;
}
