#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define TAU ( 20.0 ) //ms
#define V_REST ( -65.0 ) // mV
#define V_RESET (-65.0 ) // mV
#define THETA ( -55.0 ) // mV
#define R_M ( 1.0 ) // MOhm
#define DT ( 1.0 ) // ms
#define T ( 1000.0 ) // ms
#define NT ( 1000 ) // T / DT
#define I_EXT ( 12.0 ) // nA
#define T_REFR ( 5.0 ) //ms
#define NT_REFR ( 5 ) // T_REFR / DT

int main (void) {
    float v = V_REST;
    int32_t refr = 0;

    for (int32_t nt = 0; nt < NT; nt++) {
        float t = DT * nt;
        printf("%f %f\n", t, v);

        v += DT * (-(v - V_REST) + R_M * I_EXT) / TAU;
        bool s = (v > THETA);

        if (s) { printf("%f %f\n%f %f\n", t + DT, v, t + DT, 0.0); }

        refr = s * (NT_REFR) + (!s) * (refr - 1);
        v = ( refr > 0 ) ? V_RESET : v;
    }
}
