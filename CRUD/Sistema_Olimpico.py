import mysql.connector

# Banco de Dados MYSQL
def conectar_banco():
    conexao = mysql.connector.connect(
        host="localhost",
        user="root",             # Usuário 
        password="",             # Senha 
        database="sistema_olimpico"  # Nome do banco de dados 
    )
    return conexao

def criar_tabelas(conexao):
    cursor = conexao.cursor()
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS atletas (
            id INT AUTO_INCREMENT PRIMARY KEY,
            nome VARCHAR(255) NOT NULL,
            modalidade VARCHAR(255) NOT NULL
        )
    """)
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS participacoes (
            id INT AUTO_INCREMENT PRIMARY KEY,
            atleta_id INT,
            ano INT,
            posicao INT,
            medalha VARCHAR(255),
            FOREIGN KEY (atleta_id) REFERENCES atletas(id)
        )
    """)
    conexao.commit()

class SistemaOlimpico:
    def __init__(self, conexao):
        self.conexao = conexao

    def cadastrar_atleta(self, nome, modalidade):
        cursor = self.conexao.cursor()
        cursor.execute("INSERT INTO atletas (nome, modalidade) VALUES (%s, %s)", (nome, modalidade))
        self.conexao.commit()
        print(f"Atleta {nome} cadastrado com sucesso!\n")

    def adicionar_participacao(self, nome, ano, posicao):
        # Determinar a medalha 
        if posicao == 1:
            medalha = "Ouro"
        elif posicao == 2:
            medalha = "Prata"
        elif posicao == 3:
            medalha = "Bronze"
        else:
            medalha = "Sem medalha"

        cursor = self.conexao.cursor()
        cursor.execute("SELECT id FROM atletas WHERE nome = %s", (nome,))
        atleta_id = cursor.fetchone()
        if atleta_id:
            cursor.execute("INSERT INTO participacoes (atleta_id, ano, posicao, medalha) VALUES (%s, %s, %s, %s)",
                           (atleta_id[0], ano, posicao, medalha))
            self.conexao.commit()
            print(f"Participação de {ano} adicionada com sucesso!\n")
        else:
            print(f"Atleta {nome} não encontrado.\n")

    def listar_atletas(self):
        cursor = self.conexao.cursor()
        cursor.execute("""
            SELECT a.nome, a.modalidade, p.ano, p.posicao, p.medalha 
            FROM atletas a
            LEFT JOIN participacoes p ON a.id = p.atleta_id
            ORDER BY a.nome, p.ano
        """)
        resultados = cursor.fetchall()
        if not resultados:
            print("Nenhum atleta cadastrado.")
        else:
            for row in resultados:
                nome, modalidade, ano, posicao, medalha = row
                print(f"Nome: {nome}\nModalidade: {modalidade}\n{ano}: {posicao}° lugar ({medalha})\n" + "-" * 30)

def main():
    conexao = conectar_banco()
    criar_tabelas(conexao)
    sistema = SistemaOlimpico(conexao)

    while True:
        print("Sistema Olímpico")
        print("1. Cadastrar Atleta")
        print("2. Adicionar Participação")
        print("3. Listar Atletas")
        print("4. Sair")

        opcao = input("Escolha uma opção: ")

        if opcao == "1":
            nome = input("Nome do atleta: ")
            modalidade = input("Modalidade: ")
            sistema.cadastrar_atleta(nome, modalidade)

        elif opcao == "2":
            nome = input("Nome do atleta: ")
            ano = int(input("Ano da Olimpíada: "))
            posicao = int(input("Posição alcançada (1(ouro), 2(prata), 3(Bronze), ou outro): "))
            sistema.adicionar_participacao(nome, ano, posicao)

        elif opcao == "3":
            sistema.listar_atletas()

        elif opcao == "4":
            print("Saindo do sistema...")
            break

        else:
            print("Opção inválida!\n")

if __name__ == "__main__":
    main()
