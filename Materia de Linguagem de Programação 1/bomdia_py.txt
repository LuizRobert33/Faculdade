import sys

mensagens = {
    "--pt": "Bom dia!",
    "-1": "Bom dia!",
    "--en": "Good morning!",
    "-2": "Good morning!",
    "--es": "¡Buenos días!",
    "-3": "¡Buenos días!",
    "--fr": "Bonjour!",
    "-4": "Bonjour!",
    "--it": "Buongiorno!",
    "-5": "Buongiorno!",
    "--co": "좋은 아침이에요",
    "-6": "좋은 아침이에요",
    "--jp": "おはよう",
    "-7": "おはよう",
    "--ru": "доброе утро",
    "-8": "доброе утро"
}

def erro():
    print("Erro: Opção inválida. Utilize uma das seguintes opções:")
    print("--pt ou -1 (idioma português)")
    print("--en ou -2 (idioma inglês)")
    print("--es ou -3 (idioma espanhol)")
    print("--fr ou -4 (idioma francês)")
    print("--it ou -5 (idioma italiano)")
    print("--co ou -6 (idioma coreano)")
    print("--jp ou -7 (idioma japonês)")
    print("--ru ou -8 (idioma russo)")
    print("--help ou -h (documentação do software)")
    print("--version ou -v (versão do software)")

if len(sys.argv) != 2:
    print("Erro: Forneça uma opção.")
    erro()
else:
    opcao = sys.argv[1]
    if opcao in mensagens:
        print(mensagens[opcao])
    elif opcao in ["--help", "-h"]:
        print("Bom Dia - Software de saudação em vários idiomas.")
        print("Uso:")
        print("bomdia opção")
        print("Opções:")
        print("-h, --help Mostrar esta mensagem de ajuda.")
        print("-v, --version Mostrar a versão do software.")
        print("--pt --> Saudação em português.")
        print("--en -->  Saudação em inglês.")
        print("--es -->  Saudação em espanhol.")
        print("--fr -->  Saudação em francês.")
        print("--it -->  Saudação em italiano.")
        print("--co -->  Saudação em Coreano")
        print("--jp -->  Saudação em Japonês")
        print("--ru -->  Saudação em Russo")
    elif opcao in ["--version", "-v"]:
        print("Bom Dia - Versão 2.9")
        print("Programa feito por Luiz Roberto ©")
        print("Feito para a Disciplina de Linguagem de Programação 1")
        print("Ministrada pelo Professor Alex Pontes")
    else:
        print("Erro: Opção incorreta. Utilize uma das opções válidas.")
        erro()
