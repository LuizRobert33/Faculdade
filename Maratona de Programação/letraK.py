t, d, m = map(int, input().split())

refeicoes = []
for i in range(m):
    refeicoes.append(int(input()))

i = 0
while i < len(refeicoes) and refeicoes[i] - t >= i:
    i += 1

j = i
while j < len(refeicoes) and refeicoes[j] - t < j:
    j += 1

if i == j:
    print('Y')
else:
    print('N')