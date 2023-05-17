def verificar_voo_perfeito(T, D, M, refeicoes):
    tempo_acordado = 0

    for i in range(M):
        if refeicoes[i] - tempo_acordado > T:
            return 'N'
        
        tempo_acordado = max(tempo_acordado, refeicoes[i])

    if D - tempo_acordado > T:
        return 'N'
    
    return 'Y'

T, D, M = map(int, input().split())

refeicoes = []
for _ in range(M):
    yi = int(input())
    refeicoes.append(yi)

resultado = verificar_voo_perfeito(T, D, M, refeicoes)


print(resultado)
