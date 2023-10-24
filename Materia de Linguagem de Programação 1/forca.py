import random

# Lista de palavras secretas para o jogo
palavras = ["python", "hangman", "programacao", "desenvolvimento"]

def escolher_palavra(palavras):
    return random.choice(palavras)

def inicializar_forca(palavra):
    return ["_" for _ in palavra]

def exibir_forca(forca):
    return " ".join(forca)

def jogar_forca():
    palavra_secreta = escolher_palavra(palavras)
    tentativas = 6
    forca = inicializar_forca(palavra_secreta)
    
    print("Bem-vindo ao jogo da forca!")
    
    while tentativas > 0:
        print(f"\nPalavra: {exibir_forca(forca)}")
        print(f"Tentativas restantes: {tentativas}")
        
        letra = input("Digite uma letra: ").lower()
        
        if letra in palavra_secreta:
            for i, char in enumerate(palavra_secreta):
                if char == letra:
                    forca[i] = letra
            if "_" not in forca:
                print("You Win!")
                return
        
        else:
            print("Letra não encontrada na palavra.")
            tentativas -= 1
    
    print(f"Você perdeu! A palavra era: {palavra_secreta}")

if __name__ == "__main__":
    jogar_forca()
