#include <stdio.h>
#include <math.h>
#include <stdint.h>

#define G_SYN ( 1 )
#define SPIKE_TIMEING ( 0 )
#define TAU_DECAY ( 5.0 )
#define TAU_RISE ( 1.0 )
#define TAU_DOUBLE_PRIME ( 2.0 )
#define DT ( 0.1 ) // ms
#define T ( 30 ) // ms
#define NT ( 300 ) // T / DN

static inline double expdecay_g(const double t, const double theta) {
    return G_SYN * (exp(-(t - SPIKE_TIMEING) / 5) * theta);
}

static inline double beta_g(const double t, const double theta, const double l_b) {
    return G_SYN * l_b * theta * (
        exp(-(t - SPIKE_TIMEING) / TAU_DECAY) - exp(-(t - SPIKE_TIMEING) / TAU_RISE)
    );
}

static inline double alpha_g(const double t, const double theta) {
    return G_SYN * t * exp (1.0 - (t - SPIKE_TIMEING) / TAU_DOUBLE_PRIME) / TAU_DOUBLE_PRIME * theta;
}

int main(void) {
    double g_exp = 0;
    double g_beta = 0;
    double g_alpha = 0;

    double tau_prime = ( TAU_DECAY * TAU_RISE ) / ( TAU_DECAY - TAU_RISE );
    double l_b = 1.0 / (
            pow(TAU_RISE / TAU_DECAY, tau_prime / TAU_DECAY)
            - pow(TAU_RISE / TAU_DECAY, tau_prime / TAU_RISE)
    );

    for (int32_t nt = 0; nt <= NT; nt++) {
        double t = DT * nt;
        double theta = (t - SPIKE_TIMEING >= 0) ? 1 : 0;

        g_exp = expdecay_g(t, theta);
        g_beta = beta_g(t, theta, l_b);
        g_alpha = alpha_g(t, theta);

        printf("%f %f %f %f\n", t, g_exp, g_beta, g_alpha);
    }
}
