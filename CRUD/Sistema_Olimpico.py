import mysql.connector
import random

class SistemaOlimpico:
    def __init__(self):
        # Configuração da conexão com o banco de dados
        self.conn = mysql.connector.connect(
            host='localhost',
            user='root',
            password='',
            database='sistema_olimpico'
        )
        self.cursor = self.conn.cursor()
        self.proximo_id_modalidade = self.obter_proximo_id_modalidade()

    def obter_proximo_id_modalidade(self):
        self.cursor.execute("SELECT MAX(id) FROM modalidades")
        resultado = self.cursor.fetchone()[0]
        return (resultado or 0) + 1

    def adicionar_modalidade(self, nome_modalidade):
        self.cursor.execute("INSERT INTO modalidades (nome) VALUES (%s)", (nome_modalidade,))
        self.conn.commit()
        id_modalidade = self.proximo_id_modalidade
        print(f"Modalidade '{nome_modalidade}' cadastrada com sucesso! ID: {id_modalidade}")

    def listar_modalidades(self):
        self.cursor.execute("SELECT * FROM modalidades")
        modalidades = self.cursor.fetchall()
        if not modalidades:
            print("Nenhuma modalidade cadastrada.")
        else:
            for id_modalidade, nome in modalidades:
                print(f"ID: {id_modalidade} - Modalidade: {nome}")
        print()

    def excluir_modalidade(self, id_modalidade):
        self.cursor.execute("SELECT COUNT(*) FROM atletas WHERE modalidade_id = %s", (id_modalidade,))
        if self.cursor.fetchone()[0] > 0:
            print("Não é possível excluir a modalidade. Existem atletas associados a ela.")
        else:
            self.cursor.execute("DELETE FROM modalidades WHERE id = %s", (id_modalidade,))
            self.conn.commit()
            print(f"Modalidade com ID {id_modalidade} excluída com sucesso!")
        print()

    def cadastrar_atleta_com_participacao(self, nome, id_modalidade, participacoes):
        if id_modalidade not in [m[0] for m in self.listar_modalidades_com_ids()]:
            print(f"Erro: Modalidade com ID {id_modalidade} não encontrada.\n")
            return
        
        codigo = random.randint(100, 999)
        self.cursor.execute("INSERT INTO atletas (codigo, nome, modalidade_id) VALUES (%s, %s, %s)",
                            (codigo, nome, id_modalidade))
        
        for ano, posicao in participacoes:
            self.cursor.execute("INSERT INTO participacoes (atleta_codigo, ano, posicao) VALUES (%s, %s, %s)",
                                (codigo, ano, posicao))
        
        self.conn.commit()
        print(f"Atleta {nome} cadastrado com sucesso! Código de identificação: {codigo}\n")

    def listar_modalidades_com_ids(self):
        self.cursor.execute("SELECT id FROM modalidades")
        return self.cursor.fetchall()

    def listar_atletas(self):
        self.cursor.execute("SELECT * FROM atletas")
        atletas = self.cursor.fetchall()
        if not atletas:
            print("Nenhum atleta cadastrado.")
        else:
            for codigo, nome, modalidade_id in atletas:
                self.cursor.execute("SELECT nome FROM modalidades WHERE id = %s", (modalidade_id,))
                modalidade_nome = self.cursor.fetchone()[0]
                self.cursor.execute("SELECT * FROM participacoes WHERE atleta_codigo = %s", (codigo,))
                participacoes = self.cursor.fetchall()
                print(f"Código: {codigo}\nNome: {nome}\nModalidade: {modalidade_nome}")
                for participacao in participacoes:
                    ano, posicao = participacao[1], participacao[2]
                    medalha = "sem medalha"
                    if posicao == 1:
                        medalha = "Ouro"
                    elif posicao == 2:
                        medalha = "Prata"
                    elif posicao == 3:
                        medalha = "Bronze"
                    print(f"{ano}: {posicao}° lugar - {medalha}")
                print("-" * 30)

    def atualizar_ou_excluir_participacao(self, codigo, novo_nome=None, nova_modalidade=None, ano_excluir=None):
        if novo_nome:
            self.cursor.execute("UPDATE atletas SET nome = %s WHERE codigo = %s", (novo_nome, codigo))
        if nova_modalidade:
            if nova_modalidade in [m[0] for m in self.listar_modalidades_com_ids()]:
                self.cursor.execute("UPDATE atletas SET modalidade_id = %s WHERE codigo = %s", (nova_modalidade, codigo))
            else:
                print(f"Erro: Modalidade com ID {nova_modalidade} não encontrada.\n")
                return
        if ano_excluir:
            self.cursor.execute("DELETE FROM participacoes WHERE atleta_codigo = %s AND ano = %s", (codigo, ano_excluir))
            self.conn.commit()
            print(f"Participação de {ano_excluir} excluída com sucesso!\n")
        else:
            self.conn.commit()
            print(f"Atleta com código {codigo} atualizado com sucesso!\n")

    def excluir_atleta(self, codigo):
        self.cursor.execute("DELETE FROM participacoes WHERE atleta_codigo = %s", (codigo,))
        self.conn.commit()  
        self.cursor.execute("DELETE FROM atletas WHERE codigo = %s", (codigo,))
        self.conn.commit()  
        print(f"Atleta com código {codigo} excluído com sucesso!\n")


def main():
    sistema = SistemaOlimpico()

    while True:
        print("Sistema Olímpico")
        print("1. Adicionar Modalidade")
        print("2. Listar Modalidades")
        print("3. Excluir Modalidade")
        print("4. Cadastrar Atleta")
        print("5. Listar Atletas")
        print("6. Atualizar Atleta/Excluir Participação")
        print("7. Excluir Atleta")
        print("8. Sair")

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
            num_olimpiadas = int(input("Quantas Olimpíadas o atleta disputou? "))
            participacoes = []
            for i in range(num_olimpiadas):
                ano = int(input(f"Ano da {i+1}ª Olimpíada: "))
                posicao = int(input(f"Posição na {i+1}ª Olimpíada (1(ouro), 2(prata), 3(Bronze), ou outro): "))
                participacoes.append((ano, posicao))
            sistema.cadastrar_atleta_com_participacao(nome, id_modalidade, participacoes)

        elif opcao == "5":
            sistema.listar_atletas()

        elif opcao == "6":
            codigo = int(input("Código do atleta: "))
            novo_nome = input("Novo nome do atleta (deixe em branco para não alterar): ")
            nova_modalidade = input("Nova modalidade (ID) (deixe em branco para não alterar): ")
            nova_modalidade = int(nova_modalidade) if nova_modalidade else None
            ano_excluir = input("Ano da participação a excluir (deixe em branco para não excluir): ")
            ano_excluir = int(ano_excluir) if ano_excluir else None
            sistema.atualizar_ou_excluir_participacao(codigo, novo_nome if novo_nome else None, nova_modalidade, ano_excluir)

        elif opcao == "7":
            codigo = int(input("Código do atleta a ser excluído: "))
            sistema.excluir_atleta(codigo)

        elif opcao == "8":
            print("Saindo do sistema...")
            break

        else:
            print("Opção inválida!\n")

if __name__ == "__main__":
    main()
