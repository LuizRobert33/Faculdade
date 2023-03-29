##Problema H
##Haja Ordena¸câo
##Um amigo seu inventou um jogo e quer saber se vocˆe consegue resolvˆe-lo ou se ele ´e imposs´ıvel.
##Ele montou uma sequencia de N blocos. Cada bloco tem um n´umero gravado e uma cor. Todos
##os n´umeros s˜ao n´umeros distintos entre 1 e N, e blocos diferentes podem ter a mesma cor.
##O jogo funciona da seguinte maneira: vocˆe pode jogar quantos turnos vocˆe quiser. Em um turno,
##vocˆe escolhe dois blocos diferentes que tˆem a mesma cor e os troca de posi¸c˜ao.
##Vocˆe deve dizer se ´e poss´ıvel fazer com que a sequˆencia inteira fique em ordem crescente ou n˜ao.
##Entrada
##A primeira linha cont´em dois inteiros N e K (1 ≤ N ≤ 105
##, 1 ≤ K ≤ N), representando o n´umero
##de blocos na sequˆencia e o n´umero de cores diferentes, respectivamente.
##Cada uma das N linhas seguintes cont´em dois inteiros ni e ci (1 ≤ ni ≤ N, 1 ≤ ci ≤ K),
##representando o n´umero e a cor do i-´esimo bloco, respectivamente.
##Sa´ıda
##Imprima uma linha contendo um caracter. Se a sequˆencia puder ser ordenada em ordem crescente,
##imprima a letra mai´uscula ‘Y’; caso contr´ario, imprima a letra mai´uscula ‘N’.


n, k = map(int, input().split())
blocks = []
for i in range(n):
    number, color = map(int, input().split())
    blocks.append((number, color))

for i in range(n):
    for j in range(i + 1, n):
        if blocks[i][1] == blocks[j][1] and blocks[i][0] > blocks[j][0]:
            print('N')
            exit()

print('Y')
