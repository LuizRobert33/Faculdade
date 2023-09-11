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
}

def erro():
    print("Erro: Opção inválida. Utilize uma das seguintes opções:")
    print("--pt ou -1 (idioma português)")
    print("--en ou -2 (idioma inglês)")
    print("--es ou -3 (idioma espanhol)")
    print("--fr ou -4 (idioma francês)")
    print("--it ou -5 (idioma italiano)")
    print("--help ou -h (documentação do software)")
    print("--version ou -v (versão do software)")

if len(sys.argv) != 2:
    print("Erro: Forneça uma opção.")
    erro()
elif sys.argv[1] in ["--help", "-h"]:
    print("Bom Dia - Software de saudação em vários idiomas.")
    print("Uso:")
    print("bomdia opção")
    print("Opções:")
    print("-h, --help Mostrar esta mensagem de ajuda.")
    print("-v, --version Mostrar a versão do software.")
    print("-1, --pt --> Saudação em português.")
    print("-2, --en -->  Saudação em inglês.")
    print("-3, --es -->  Saudação em espanhol.")
    print("-4, --fr -->  Saudação em francês.")
    print("-5, --it -->  Saudação em italiano.")
elif sys.argv[1] == "--version" or sys.argv[1] == "-v":
    print("Bom Dia - Versão 2.9")
else:
    print("Erro: Opção incorreta. Utilize uma das opções válidas.")
    erro()
