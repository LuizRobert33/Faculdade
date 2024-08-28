import random

class SistemaOlimpico:
    def __init__(self):
        self.atletas = {}  # Armazena atletas com o código de identificação(de 3 digitos)
        self.participacoes = []  # Lista de participações
        self.modalidades = {}  # Armazena modalidades com ID como chave
        self.proximo_id_modalidade = 1  # ID para novas modalidades

    def gerar_codigo(self):
        """Gera um código único para o atleta."""
        while True:
            codigo = random.randint(100, 999)
            if codigo not in self.atletas:
                return codigo

    def adicionar_modalidade(self, nome_modalidade):
        """Adiciona uma nova modalidade com um ID único."""
        self.modalidades[self.proximo_id_modalidade] = nome_modalidade
        print(f"Modalidade '{nome_modalidade}' cadastrada com sucesso! ID: {self.proximo_id_modalidade}")
        self.proximo_id_modalidade += 1

    def listar_modalidades(self):
        """Lista todas as modalidades cadastradas."""
        if not self.modalidades:
            print("Nenhuma modalidade cadastrada.")
        else:
            for id_modalidade, nome in self.modalidades.items():
                print(f"ID: {id_modalidade} - Modalidade: {nome}")
        print()

    def excluir_modalidade(self, id_modalidade):
        """Remove uma modalidade com base no ID fornecido."""
        if id_modalidade in self.modalidades:
            
            if any(atleta['modalidade'] == self.modalidades[id_modalidade] for atleta in self.atletas.values()):
                print("Não é possível excluir a modalidade. Existem atletas associados a ela.")
            else:
                del self.modalidades[id_modalidade]
                print(f"Modalidade com ID {id_modalidade} excluída com sucesso!")
        else:
            print(f"Erro: Modalidade com ID {id_modalidade} não encontrada.")
        print()

    def cadastrar_atleta(self, nome, id_modalidade):
        """Cadastra um novo atleta com um código gerado automaticamente."""
        if id_modalidade not in self.modalidades:
            print(f"Erro: Modalidade com ID {id_modalidade} não encontrada.\n")
            return

        codigo = self.gerar_codigo()
        self.atletas[codigo] = {
            'nome': nome,
            'modalidade': self.modalidades[id_modalidade]
        }
        print(f"Atleta {nome} cadastrado com sucesso! Código de identificação: {codigo}\n")

    def adicionar_participacao(self, codigo, ano, posicao):
        """Adiciona uma participação para um atleta existente."""
        if codigo in self.atletas:
            # Determinar a medalha 
            if posicao == 1:
                medalha = "Ouro"
            elif posicao == 2:
                medalha = "Prata"
            elif posicao == 3:
                medalha = "Bronze"
            else:
                medalha = "Sem medalha"

            self.participacoes.append({
                'codigo': codigo,
                'ano': ano,
                'posicao': posicao,
                'medalha': medalha
            })
            print(f"Participação de {ano} adicionada com sucesso!\n")
        else:
            print(f"Atleta com código {codigo} não encontrado.\n")

    def listar_atletas(self):
        """Lista todos os atletas e suas participações."""
        if not self.atletas:
            print("Nenhum atleta cadastrado.")
        else:
            for codigo, info in self.atletas.items():
                print(f"Código: {codigo}\nNome: {info['nome']}\nModalidade: {info['modalidade']}")
                for participacao in self.participacoes:
                    if participacao['codigo'] == codigo:
                        print(f"{participacao['ano']}: {participacao['posicao']}° lugar ({participacao['medalha']})")
                print("-" * 30)

    def atualizar_ou_excluir_participacao(self, codigo, novo_nome=None, nova_modalidade=None, ano_excluir=None):
        """Atualiza o nome e/ou a modalidade de um atleta, ou exclui uma participação de um ano específico."""
        if codigo in self.atletas:
            if novo_nome:
                self.atletas[codigo]['nome'] = novo_nome
            if nova_modalidade:
                if nova_modalidade in self.modalidades:
                    self.atletas[codigo]['modalidade'] = self.modalidades[nova_modalidade]
                else:
                    print(f"Erro: Modalidade com ID {nova_modalidade} não encontrada.\n")
                    return
            if ano_excluir:
                self.participacoes = [p for p in self.participacoes if not (p['codigo'] == codigo and p['ano'] == ano_excluir)]
                print(f"Participação de {ano_excluir} excluída com sucesso!\n")
            else:
                print(f"Atleta com código {codigo} atualizado com sucesso!\n")
        else:
            print(f"Atleta com código {codigo} não encontrado.\n")

    def excluir_atleta(self, codigo):
        """Exclui um atleta baseado no código. Remove também as participações associadas."""
        if codigo in self.atletas:
            del self.atletas[codigo]
            self.participacoes = [p for p in self.participacoes if p['codigo'] != codigo]
            print(f"Atleta com código {codigo} excluído com sucesso!\n")
        else:
            print(f"Atleta com código {codigo} não encontrado.\n")

def main():
    sistema = SistemaOlimpico()

    while True:
        print("Sistema Olímpico")
        print("1. Adicionar Modalidade")
        print("2. Listar Modalidades")
        print("3. Excluir Modalidade")
        print("4. Cadastrar Atleta")
        print("5. Adicionar Participação")
        print("6. Listar Atletas")
        print("7. Atualizar Atleta/Excluir Participação")
        print("8. Excluir Atleta")
        print("9. Sair")

        opcao = input("Escolha uma opção: ")

        if opcao == "1":
            nome_modalidade = input("Nome da modalidade: ")
            sistema.adicionar_modalidade(nome_modalidade)

        elif opcao == "2":
            sistema.listar_modalidades()

        elif opcao == "3":
            id_modalidade = int(input("ID da modalidade a ser excluída: "))
            sistema.excluir_modalidade(id_modalidade)

        elif opcao == "4":
            sistema.listar_modalidades()
            id_modalidade = int(input("ID da modalidade: "))
            nome = input("Nome do atleta: ")
            sistema.cadastrar_atleta(nome, id_modalidade)

        elif opcao == "5":
            codigo = int(input("Código do atleta: "))
            ano = int(input("Ano da Olimpíada: "))
            posicao = int(input("Posição alcançada (1(ouro), 2(prata), 3(Bronze), ou outro): "))
            sistema.adicionar_participacao(codigo, ano, posicao)

        elif opcao == "6":
            sistema.listar_atletas()

        elif opcao == "7":
            codigo = int(input("Código do atleta: "))
            novo_nome = input("Novo nome do atleta (deixe em branco para não alterar): ")
            nova_modalidade = input("Nova modalidade (ID) (deixe em branco para não alterar): ")
            nova_modalidade = int(nova_modalidade) if nova_modalidade else None
            ano_excluir = input("Ano da participação a excluir (deixe em branco para não excluir): ")
            ano_excluir = int(ano_excluir) if ano_excluir else None
            sistema.atualizar_ou_excluir_participacao(codigo, novo_nome if novo_nome else None, nova_modalidade, ano_excluir)

        elif opcao == "8":
            codigo = int(input("Código do atleta a ser excluído: "))
            sistema.excluir_atleta(codigo)

        elif opcao == "9":
            print("Saindo do sistema...")
            break

        else:
            print("Opção inválida!\n")

if __name__ == "__main__":
    main()
