
def calcular_maximo_questoes(A, B, C, tipo_desejado):
    tipo_desejado = tipo_desejado.upper()
    
    if tipo_desejado == 'A':
        if C%2 != 0:
            A += (C*5//2)
        else:
            A += C*5    
        A+= (3*B)//2     
        return A
    elif tipo_desejado == 'B':
        E = int( (C*5/2)*2)
        B +=  E//3
        B += (2*A)//3
        return B
    elif tipo_desejado == 'C':
        C += (A // 3) * 2
        C += (((3*B)//2) // 3)*2   
        return C

A, B, C,= [int(x) for x in input().split()]
tipo_desejado = input()
maximo_questoes = calcular_maximo_questoes(A, B, C, tipo_desejado)
print(maximo_questoes)
