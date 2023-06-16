T = int(input("Minutos a Dormir: "))
D = int(input("Tempo de voo: "))
M = int(input("Numero de refeições: "))
refeicoes = list()
for c in range(0,M):
    R = int(input("Refeição: "))
    refeicoes.append(R)
while True:
    if T>D:
        print("N")
        break
for tempo_refeicao in refeicoes:
    if tempo_refeicao - T <= refeicoes[0]:
        print("N")
        break
else:
    print("Y")




