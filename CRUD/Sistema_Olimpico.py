import random
import os
import shutil
import mysql.connector

class SistemaOlimpico:
    def __init__(self):
        self.atletas = {}
        self.modalidades = {}
        self.proximo_id_modalidade = 1

        # Conectar ao banco de dados MySQL
        self.conexao = self.conectar_mysql()
        self.carregar_dados_iniciais()

    def conectar_mysql(self):
        """Conecta ao banco de dados MySQL."""
        try:
            conexao = mysql.connector.connect(
                host="localhost",
                user="root",  
                password="",  
                database="sistema_olimpico"
            )
            print("\n\033[92mConexão com o banco de dados MySQL estabelecida com sucesso!\033[0m")
            return conexao
        except mysql.connector.Error as err:
            print(f"\n\033[91mErro ao conectar ao MySQL: {err}\033[0m")
            exit()

    def carregar_dados_iniciais(self):
        """Carrega modalidades e atletas do banco de dados."""
        cursor = self.conexao.cursor(dictionary=True)

       
        cursor.execute("SELECT * FROM modalidades")
        for modalidade in cursor.fetchall():
            self.modalidades[modalidade['id']] = modalidade['nome']
            if modalidade['id'] >= self.proximo_id_modalidade:
                self.proximo_id_modalidade = modalidade['id'] + 1

        
        cursor.execute("SELECT * FROM atletas")
        atletas = cursor.fetchall()
        for atleta in atletas:
            cursor.execute(f"SELECT * FROM participacoes WHERE codigo_atleta = {atleta['codigo']}")
            participacoes = cursor.fetchall()
            self.atletas[atleta['codigo']] = {
                'nome': atleta['nome'],
                'sexo': atleta['sexo'],
                'modalidade': self.modalidades[atleta['id_modalidade']],
                'participacoes': [{'ano': p['ano'], 'posicao': p['posicao'], 'medalha': p['medalha']} for p in participacoes]
            }

        cursor.close()

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

        cursor = self.conexao.cursor()
        cursor.execute("INSERT INTO modalidades (nome) VALUES (%s)", (nome_modalidade,))
        self.conexao.commit()

        self.modalidades[self.proximo_id_modalidade] = nome_modalidade
        print(f"\n\033[92mModalidade '{nome_modalidade}' cadastrada com sucesso!\033[0m ID: {self.proximo_id_modalidade}")
        self.proximo_id_modalidade += 1

        cursor.close()

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
                cursor = self.conexao.cursor()
                cursor.execute("DELETE FROM modalidades WHERE id = %s", (id_modalidade,))
                self.conexao.commit()

                del self.modalidades[id_modalidade]
                print(f"\n\033[92mModalidade com ID {id_modalidade} excluída com sucesso!\033[0m")

                cursor.close()
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

        
        if sexo not in ['M', 'F']:
            print("\n\033[91mErro: Sexo deve ser 'M' para Masculino ou 'F' para Feminino.\033[0m")
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

        cursor = self.conexao.cursor()
        cursor.execute("INSERT INTO atletas (codigo, nome, sexo, id_modalidade) VALUES (%s, %s, %s, %s)", 
                       (codigo, nome, sexo, id_modalidade))
        for part in participacoes:
            cursor.execute("INSERT INTO participacoes (codigo_atleta, ano, posicao, medalha) VALUES (%s, %s, %s, %s)",
                           (codigo, part['ano'], part['posicao'], part['medalha']))
        self.conexao.commit()

        self.atletas[codigo] = {
            'nome': nome,
            'modalidade': self.modalidades[id_modalidade],
            'sexo': sexo,
            'participacoes': participacoes
        }

        print(f"\n\033[92mAtleta {nome} cadastrado com sucesso!\033[0m Código de identificação: {codigo}")

        cursor.close()

    def listar_atletas(self):
        """Lista todos os atletas e suas participações."""
        if not self.atletas:
            print("\n\033[91mNenhum atleta cadastrado.\033[0m")
        else:
            print("\n\033[94mAtletas cadastrados:\033[0m")
            for codigo, atleta in self.atletas.items():
                sexo_completo = "Masculino" if atleta['sexo'] == 'M' else "Feminino"
                print(f"Código: {codigo} - Nome: {atleta['nome']} - Modalidade: {atleta['modalidade']} - Sexo: {sexo_completo}")
                for part in atleta['participacoes']:
                    print(f"  - Ano: {part['ano']} - Posição: {part['posicao']} - Medalha: {part['medalha']}")

    def atualizar_ou_excluir_participacao(self, codigo, novo_nome, nova_modalidade, novo_sexo, ano_excluir):
        """Atualiza os dados do atleta ou exclui uma participação específica."""
        if codigo not in self.atletas:
            print(f"\n\033[91mErro: Atleta com código {codigo} não encontrado.\033[0m")
            return

        cursor = self.conexao.cursor()

        if novo_nome:
            cursor.execute("UPDATE atletas SET nome = %s WHERE codigo = %s", (novo_nome, codigo))
            self.atletas[codigo]['nome'] = novo_nome

        if nova_modalidade:
            cursor.execute("UPDATE atletas SET id_modalidade = %s WHERE codigo = %s", (nova_modalidade, codigo))
            self.atletas[codigo]['modalidade'] = self.modalidades[nova_modalidade]

        if novo_sexo:
            if novo_sexo not in ['M', 'F']:
                print("\n\033[91mErro: Sexo deve ser 'M' para Masculino ou 'F' para Feminino.\033[0m")
                return
            cursor.execute("UPDATE atletas SET sexo = %s WHERE codigo = %s", (novo_sexo, codigo))
            self.atletas[codigo]['sexo'] = novo_sexo

        if ano_excluir:
            cursor.execute("DELETE FROM participacoes WHERE codigo_atleta = %s AND ano = %s", (codigo, ano_excluir))
            self.atletas[codigo]['participacoes'] = [p for p in self.atletas[codigo]['participacoes'] if p['ano'] != ano_excluir]

        self.conexao.commit()
        cursor.close()

    def excluir_atleta(self, codigo):
        """Exclui um atleta com base no código fornecido."""
        if codigo in self.atletas:
            cursor = self.conexao.cursor()
            cursor.execute("DELETE FROM atletas WHERE codigo = %s", (codigo,))
            cursor.execute("DELETE FROM participacoes WHERE codigo_atleta = %s", (codigo,))
            self.conexao.commit()

            del self.atletas[codigo]
            print(f"\n\033[92mAtleta com código {codigo} excluído com sucesso!\033[0m")

            cursor.close()
        else:
            print(f"\n\033[91mErro: Atleta com código {codigo} não encontrado.\033[0m")

    def menu(self):
        """Exibe o menu principal do sistema."""
        while True:
            self.limpar_tela()
            print(self.centralizar_texto("\033[1;36mSistema Olímpico\033[0m"))
            print(self.centralizar_texto("\033[1;33m1. Cadastrar Modalidade\033[0m"))
            print(self.centralizar_texto("\033[1;33m2. Listar Modalidades\033[0m"))
            print(self.centralizar_texto("\033[1;33m3. Excluir Modalidade\033[0m"))
            print(self.centralizar_texto("\033[1;33m4. Cadastrar Atleta\033[0m"))
            print(self.centralizar_texto("\033[1;33m5. Listar Atletas\033[0m"))
            print(self.centralizar_texto("\033[1;33m6. Atualizar/Excluir Participação de Atleta\033[0m"))
            print(self.centralizar_texto("\033[1;33m7. Excluir Atleta\033[0m"))
            print(self.centralizar_texto("\033[1;31m0. Sair\033[0m"))

            opcao = input("\nEscolha uma opção: ")
            self.limpar_tela()

            if opcao == '1':
                nome_modalidade = input("Digite o nome da nova modalidade: ")
                self.adicionar_modalidade(nome_modalidade)
            elif opcao == '2':
                self.listar_modalidades()
            elif opcao == '3':
                id_modalidade = int(input("Digite o ID da modalidade a ser excluída: "))
                self.excluir_modalidade(id_modalidade)
            elif opcao == '4':
                nome = input("Digite o nome do atleta: ")
                self.listar_modalidades()
                id_modalidade = int(input("Digite o ID da modalidade do atleta: "))
                sexo = input("Digite o sexo do atleta (M para Masculino, F para Feminino): ").upper()
                self.cadastrar_atleta(nome, id_modalidade, sexo)
            elif opcao == '5':
                self.listar_atletas()
            elif opcao == '6':
                codigo = int(input("Digite o código do atleta a ser atualizado/excluído: "))
                novo_nome = input("Digite o novo nome do atleta (ou deixe em branco para não alterar): ")
                self.listar_modalidades()
                nova_modalidade = input("Digite o novo ID da modalidade do atleta (ou deixe em branco para não alterar): ")
                if nova_modalidade:
                    nova_modalidade = int(nova_modalidade)
                novo_sexo = input("Digite o novo sexo do atleta (M para Masculino, F para Feminino) (ou deixe em branco para não alterar): ").upper()
                ano_excluir = input("Digite o ano da participação a ser excluída (ou deixe em branco para não excluir): ")
                if ano_excluir:
                    ano_excluir = int(ano_excluir)
                self.atualizar_ou_excluir_participacao(codigo, novo_nome, nova_modalidade, novo_sexo, ano_excluir)
            elif opcao == '7':
                codigo = int(input("Digite o código do atleta a ser excluído: "))
                self.excluir_atleta(codigo)
            elif opcao == '0':
                self.conexao.close()
                print("\n\033[92mSaindo do sistema...\033[0m")
                break
            else:
                print("\n\033[91mOpção inválida. Tente novamente.\033[0m")

            self.pausar()

# Executando o sistema
if __name__ == "__main__":
    sistema = SistemaOlimpico()
    sistema.menu()


"""""
-- Cria o banco de dados se não existir
CREATE DATABASE IF NOT EXISTS sistema_olimpico;

-- Usa o banco de dados criado
USE sistema_olimpico;

-- Cria a tabela de modalidades
CREATE TABLE IF NOT EXISTS modalidades (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL
);

-- Cria a tabela de atletas
CREATE TABLE IF NOT EXISTS atletas (
    codigo INT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    sexo CHAR(1) NOT NULL,
    id_modalidade INT,
    FOREIGN KEY (id_modalidade) REFERENCES modalidades(id)
);

-- Cria a tabela de participações
CREATE TABLE IF NOT EXISTS participacoes (
    id INT AUTO_INCREMENT PRIMARY KEY,
    codigo_atleta INT,
    ano INT,
    posicao INT,
    medalha VARCHAR(50),
    FOREIGN KEY (codigo_atleta) REFERENCES atletas(codigo)
);


SHOW DATABASES;
USE sistema_olimpico;
SHOW TABLES;




"""