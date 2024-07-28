// Exercicos de impressão de Horas
#include <stdio.h>

int main() {
    // Loop para horas (de 23 até 0)
    for (int hour = 23; hour >= 0; hour--) {
        // Loop para minutos (de 59 até 0)
        for (int minute = 59; minute >= 0; minute--) {
            // Loop para segundos (de 59 até 0)
            for (int second = 59; second >= 0; second--) {
                // Imprime o tempo no formato HH:MM:SS
                printf("%02d:%02d:%02d\n", hour, minute, second);
            }
        }
    }

    return 0;
}
