


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
