#include <stdio.h>

int contarCaractere(const char *string, char caractere) {
    int contador = 0;
    
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == caractere) {
            contador++;
        }
    }
    
    return contador;
}

int main() {
    const char *minhaString = "Exemplo de frase com caracteres.";
    char meuCaractere = 'e';
    
    int resultado = contarCaractere(minhaString, meuCaractere);
    
    printf("O caractere '%c' aparece %d vezes na string.\n", meuCaractere, resultado);
    
    return 0;
}
