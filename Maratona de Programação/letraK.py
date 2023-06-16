def voo_perfeito(T, D, M, tempos_refeicoes):
    # Verifica se é possível dormir tempo suficiente e comer todas as refeições
    for i in range(M-1):
        if tempos_refeicoes[i+1] - tempos_refeicoes[i] > T:
            return 'N'  # Não é possível dormir tempo suficiente para comer todas as refeições
    
    # Verifica se é possível dormir tempo suficiente até o final do voo
    if D - tempos_refeicoes[M-1] > T:
        return 'Y'  # É possível dormir e comer todas as refeições
    
    if tempos_refeicoes[0] - 1 > T:
        return 'Y'  # É possível dormir até o início da primeira refeição
    
    return 'N'  # Não é possível dormir tempo suficiente até o final do voo


# Leitura da entrada
T, D, M = map(int, input().split())
tempos_refeicoes = [int(input()) for _ in range(M)]

# Chamada da função
resultado = voo_perfeito(T, D, M, tempos_refeicoes)

# Impressão do resultado
print(resultado)
