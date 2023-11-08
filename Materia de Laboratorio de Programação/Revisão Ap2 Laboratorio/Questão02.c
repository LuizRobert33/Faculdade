/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <string.h>

struct estoque {
    int codigo;
    char Nome[20];
    char Marca[20];
    float Preço;
};

int main() {
    struct estoque c[10];
    int escolha;
    int contador = 0;

    while (1) {
        printf("MENU DE ESCOLHAS:\n");
        printf("1 - CADASTRAR PRODUTO\n");
        printf("2 - LISTAR PRODUTOS EM ORDEM ALFABÉTICA\n");
        printf("3 - EXCLUIR PRODUTO\n");
        printf("4 - SAIR\n");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                if (contador < 10) {
                    printf("Digite o código do produto: ");
                    scanf("%d", &c[contador].codigo);
                    printf("Digite o Nome do produto: ");
                    scanf("%s", c[contador].Nome);
                    printf("Digite o Nome da Marca: ");
                    scanf("%s", c[contador].Marca);
                    printf("Digite o Preço: ");
                    scanf("%f", &c[contador].Preço);
                    contador++;
                    printf("Produto Cadastrado com Sucesso\n");
                } else {
                    printf("O estoque está cheio. Não é possível cadastrar mais produtos.\n");
                }
                break;

            case 2:
                if (contador > 0) {
                    for (int i = 0; i < contador - 1; i++) {
                        for (int j = 0; j < contador - i - 1; j++) {
                            if (strcmp(c[j].Nome, c[j + 1].Nome) > 0) {
                                struct estoque temp = c[j];
                                c[j] = c[j + 1];
                                c[j + 1] = temp;
                            }
                        }
                    }
                    printf("Produtos em ordem alfabética:\n");
                    for (int i = 0; i < contador; i++) {
                        printf("Código: %d, Nome: %s, Marca: %s, Preço: %.2f\n",
                               c[i].codigo, c[i].Nome, c[i].Marca, c[i].Preço);
                    }
                }
                break;

            case 3:
                if (contador > 0) {
                    int codigoExcluir;
                    printf("Digite o código do produto a ser excluído: ");
                    scanf("%d", &codigoExcluir);

                    int encontrado = 0;
                    for (int i = 0; i < contador; i++) {
                        if (c[i].codigo == codigoExcluir) {
                            for (int j = i; j < contador - 1; j++) {
                                c[j] = c[j + 1];
                            }
                            contador--;
                            printf("Produto com código %d foi excluído.\n", codigoExcluir);
                            encontrado = 1;
                            break;
                        }
                    }
                    if (!encontrado) {
                        printf("Produto com código %d não encontrado.\n", codigoExcluir);
                    }
                }
                break;

            case 4:
                printf("Saindo do programa...\n");
                return 0;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}
