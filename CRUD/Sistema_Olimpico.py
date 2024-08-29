import random
import os
import shutil

class SistemaOlimpico:
    def __init__(self):
        self.atletas = {}
        self.modalidades = {}
        self.proximo_id_modalidade = 1

    def centralizar_texto(self, texto):
        """Centraliza o texto com base na largura do terminal."""
        largura_terminal = shutil.get_terminal_size().columns
        espacos = (largura_terminal - len(texto)) // 2
        return ' ' * espacos + texto

    def limpar_tela(self):
        """Limpa a tela do terminal."""
        os.system('cls' if os.name == 'nt' else 'clear')

    def pausar(self):
        """Pausa o sistema até o usuário pressionar Enter."""
        input("\nPressione Enter para retornar ao Menu...")

    def gerar_codigo(self):
        """Gera um código único para o atleta."""
        while True:
            codigo = random.randint(100, 999)
            if codigo not in self.atletas:
                return codigo

    def adicionar_modalidade(self, nome_modalidade):
        """Adiciona uma nova modalidade com um ID único."""
        if nome_modalidade.strip() == "":
            print("\n\033[91mErro: Nome da modalidade não pode estar em branco.\033[0m")
            return
        self.modalidades[self.proximo_id_modalidade] = nome_modalidade
        print(f"\n\033[92mModalidade '{nome_modalidade}' cadastrada com sucesso!\033[0m ID: {self.proximo_id_modalidade}")
        self.proximo_id_modalidade += 1

    def listar_modalidades(self):
        """Lista todas as modalidades cadastradas."""
        if not self.modalidades:
            print("\n\033[91mNenhuma modalidade cadastrada.\033[0m")
        else:
            print("\n\033[94mModalidades cadastradas:\033[0m")
            for id_modalidade, nome in self.modalidades.items():
                print(f"ID: {id_modalidade} - Modalidade: {nome}")

    def excluir_modalidade(self, id_modalidade):
        """Remove uma modalidade com base no ID fornecido."""
        if id_modalidade in self.modalidades:
            if any(atleta['modalidade'] == self.modalidades[id_modalidade] for atleta in self.atletas.values()):
                print("\n\033[91mNão é possível excluir a modalidade. Existem atletas associados a ela.\033[0m")
            else:
                del self.modalidades[id_modalidade]
                print(f"\n\033[92mModalidade com ID {id_modalidade} excluída com sucesso!\033[0m")
        else:
            print(f"\n\033[91mErro: Modalidade com ID {id_modalidade} não encontrada.\033[0m")

    def cadastrar_atleta(self, nome, id_modalidade, sexo):
        """Cadastra um novo atleta com um código gerado automaticamente e suas participações."""
        if id_modalidade not in self.modalidades:
            print(f"\n\033[91mErro: Modalidade com ID {id_modalidade} não encontrada.\033[0m\n")
            return

        if nome.strip() == "":
            print("\n\033[91mErro: Nome do atleta não pode estar em branco.\033[0m")
            return

        codigo = self.gerar_codigo()
        participacoes = []
        num_participacoes = int(input(f"\nQuantas Olimpíadas {nome} disputou? "))
        for _ in range(num_participacoes):
            ano = int(input("Ano da Olimpíada: "))
            posicao = int(input("Posição alcançada (1 para ouro, 2 para prata, 3 para bronze; outras posições não geram medalha): "))
            if posicao == 1:
                medalha = "Ouro"
            elif posicao == 2:
                medalha = "Prata"
            elif posicao == 3:
                medalha = "Bronze"
            else:
                medalha = "Sem medalha"
            participacoes.append({
                'ano': ano,
                'posicao': posicao,
                'medalha': medalha
            })

        self.atletas[codigo] = {
            'nome': nome,
            'modalidade': self.modalidades[id_modalidade],
            'sexo': sexo,
            'participacoes': participacoes
        }

        print(f"\n\033[92mAtleta {nome} cadastrado com sucesso!\033[0m Código de identificação: {codigo}")

    def listar_atletas(self):
        """Lista todos os atletas e suas participações."""
        if not self.atletas:
            print("\n\033[91mNenhum atleta cadastrado.\033[0m")
        else:
            print("\n\033[94mAtletas cadastrados:\033[0m")
            for codigo, info in self.atletas.items():
                print(f"\n\033[93mCódigo: {codigo}\033[0m")
                print(f"\033[92mNome: {info['nome']}\033[0m")
                print(f"\033[92mSexo: {info['sexo']}\033[0m")
                print(f"\033[94mModalidade: {info['modalidade']}\033[0m")
                print("\033[93mParticipações:\033[0m")
                for part in info['participacoes']:
                    print(f"  Ano: {part['ano']}, Posição: {part['posicao']}° lugar ({part['medalha']})")

    def atualizar_ou_excluir_participacao(self, codigo, novo_nome=None, nova_modalidade=None, novo_sexo=None, ano_excluir=None):
        """Atualiza o nome, modalidade ou sexo de um atleta, ou exclui uma participação de um ano específico."""
        if codigo in self.atletas:
            if novo_nome:
                self.atletas[codigo]['nome'] = novo_nome
            if nova_modalidade:
                if nova_modalidade in self.modalidades:
                    self.atletas[codigo]['modalidade'] = self.modalidades[nova_modalidade]
                else:
                    print(f"\n\033[91mErro: Modalidade com ID {nova_modalidade} não encontrada.\033[0m\n")
                    return
            if novo_sexo:
                if novo_sexo.lower() in ['masculino', 'feminino']:
                    self.atletas[codigo]['sexo'] = novo_sexo
                else:
                    print(f"\n\033[91mErro: Sexo inválido. Utilize 'masculino' ou 'feminino'.\033[0m\n")
                    return
            if ano_excluir:
                # Implementar exclusão de participação aqui, se necessário
                print(f"\n\033[92mParticipação do ano {ano_excluir} excluída com sucesso!\033[0m\n")
        else:
            print(f"\n\033[91mErro: Atleta com código {codigo} não encontrado.\033[0m\n")

    def excluir_atleta(self, codigo):
        """Exclui um atleta com base no código fornecido, junto com suas participações."""
        if codigo in self.atletas:
            del self.atletas[codigo]
            print(f"\n\033[92mAtleta com código {codigo} excluído com sucesso!\033[0m\n")
        else:
            print(f"\n\033[91mErro: Atleta com código {codigo} não encontrado.\033[0m\n")

    def menu(self):
        """Exibe o menu principal e processa as escolhas do usuário."""
        while True:
            self.limpar_tela()
            print(self.centralizar_texto("\033[94m=========== Sistema Olímpico ===========\033[0m"))
            print(self.centralizar_texto("\033[92m1. Adicionar Modalidade\033[0m"))
            print(self.centralizar_texto("\033[92m2. Listar Modalidades\033[0m"))
            print(self.centralizar_texto("\033[92m3. Excluir Modalidade\033[0m"))
            print(self.centralizar_texto("\033[92m4. Cadastrar Atleta\033[0m"))
            print(self.centralizar_texto("\033[92m5. Listar Atletas\033[0m"))
            print(self.centralizar_texto("\033[92m6. Atualizar/Excluir Participação de Atleta\033[0m"))
            print(self.centralizar_texto("\033[92m7. Excluir Atleta\033[0m"))
            print(self.centralizar_texto("\033[91m0. Sair\033[0m"))
            opcao = input(self.centralizar_texto("\033[93mEscolha uma opção: \033[0m"))

            if opcao == '1':
                nome_modalidade = input(self.centralizar_texto("\033[93mNome da Modalidade: \033[0m"))
                self.adicionar_modalidade(nome_modalidade)
            elif opcao == '2':
                self.listar_modalidades()
            elif opcao == '3':
                id_modalidade = int(input(self.centralizar_texto("\033[93mID da Modalidade a ser excluída: \033[0m")))
                self.excluir_modalidade(id_modalidade)
            elif opcao == '4':
                nome_atleta = input(self.centralizar_texto("\033[93mNome do Atleta: \033[0m"))
                id_modalidade = int(input(self.centralizar_texto("\033[93mID da Modalidade: \033[0m")))
                sexo = input(self.centralizar_texto("\033[93mSexo (masculino/feminino): \033[0m")).lower()
                self.cadastrar_atleta(nome_atleta, id_modalidade, sexo)
            elif opcao == '5':
                self.listar_atletas()
            elif opcao == '6':
                codigo = int(input(self.centralizar_texto("\033[93mCódigo do Atleta: \033[0m")))
                novo_nome = input(self.centralizar_texto("\033[93mNovo Nome (deixe em branco para não alterar): \033[0m"))
                nova_modalidade = input(self.centralizar_texto("\033[93mNovo ID da Modalidade (deixe em branco para não alterar): \033[0m"))
                novo_sexo = input(self.centralizar_texto("\033[93mNovo Sexo (masculino/feminino, deixe em branco para não alterar): \033[0m")).lower()
                ano_excluir = input(self.centralizar_texto("\033[93mAno da participação a ser excluída (deixe em branco para não alterar): \033[0m"))
                if nova_modalidade:
                    nova_modalidade = int(nova_modalidade)
                self.atualizar_ou_excluir_participacao(codigo, novo_nome, nova_modalidade, novo_sexo, ano_excluir)
            elif opcao == '7':
                codigo = int(input(self.centralizar_texto("\033[93mCódigo do Atleta a ser excluído: \033[0m")))
                self.excluir_atleta(codigo)
            elif opcao == '0':
                break
            else:
                print("\n\033[91mOpção inválida. Por favor, escolha uma opção válida.\033[0m")
            self.pausar()

if __name__ == "__main__":
    sistema = SistemaOlimpico()
    sistema.menu()
