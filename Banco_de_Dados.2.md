# Tarefa
Davi Lucas Gomes de Araújo
### 1. Pesquise quais são os tipos de dados suportados pelo PostgreSQL e quantidade de memória necessária para armazenar cada um.
De acordo com a documentação oficial do postgresql, há mais de 20 tipos de dados que podem ser inseridos, mas o que nos interessa são os seguintes tipos, são eles: 
- Numeric Types
- Monetary Types
- Character Types
- Date/Time Types
- Boolean Type
- Enumerated Types
- UUID Type
#### Tabela de Numeric Types

| Nome dos numéricos | Tamanho em Bytes | Observações                        |
| ------------------ | :--------------: | ---------------------------------- |
| smallint           |        2         |                                    |
| integer            |        4         |                                    |
| bigint             |        8         |                                    |
| decimal            |     Variável     | Precisão especificada pelo usuário |
| numeric            |     Variável     | Precisão especificada pelo usuário |
| real               |        4         |                                    |
| double precision   |        8         |                                    |
| smallserial        |        2         |                                    |
| serial             |        4         |                                    |
| bigserial          |        8         |                                    |
#### Monetary Types
O tipo `monetary` ocupa 8 bytes, com uma precisão fracionária fixa(0.00, por exemplo), mas também pode ser definida na banco de dados de configuração `lc_monetary`. A entrada inclusive pode incluir os símbolos de entrada, e a saída também, tudo dependendo da localidade.
Esse tipo de dado pode ser convertido para `numeric` sem perca de precisão, mas para outros tipos pode ser que haja perda de informação. Além disso, tipos de dados como `numeric`, `int`, `bigint` podem ser convertidos para `monetary`.
#### Character Types

| Nome                       | Tamanho em bytes            | Observações                                                    |
| -------------------------- | --------------------------- | -------------------------------------------------------------- |
| character varying, varchar | Tamanho variável com limite |                                                                |
| character, char, bpchar    | Tamanho fixo                | Caso não seja totalmente ocupado, é ocupado com espaço         |
| bpchar                     | Tamanho variável ilimitado  | Caso não seja totalmente ocupado, o espaço extra é cortado<br> |
| text                       | Tamanho variável ilimitado  |                                                                |
O tipo é chamado no script sql assim `character(n)`, onde `n` significa um inteiro positivo e `character` qualquer um dos tipos de texto listado acima. Um adendo que no UTF-8, caracteres ASCII comuns ocupam 1 byte cada, caracteres acentuados ocupam geralmente 2 bytes e alguns símbolos/emojis ocupam até **4 bytes**
#### Date/Time Types

| Nome      | Tamanho em bytes | Observações                          |
| --------- | ---------------- | ------------------------------------ |
| timestamp | 8                | Possui tempo e data sem fuso horário |
| timestamp | 8                | Possui tempo e data com fuso horário |
| date      | 4                | Apenas data                          |
| time      | 8                | Apenas tempo                         |
| time      | 12               | Apenas tempo com fuso horário        |
| interval  | 16               | Intervalo de tempo                   |
#### Boolean Type
O `boolean` possui apenas 1 byte de tamanho, e salva os valores `TRUE, YES, ON, 1` para o estado verdadeiro, e `FALSE, NO, OFF, 0` para o estado falso.
#### UUID Type
`UUID` significa `Universally Unique Identifiers`. Esse identificador tem o tamanho de 128 bits(16 bytes) gerado por um algoritmo que torna muito improvável que o mesmo identificador seja gerado por outra pessoa no universo conhecido usando o mesmo algoritmo. Achei importante trazer porque é uma saída para identificadores nos bancos de dados.
#### 2. Quais são os tipos de arquivos suportados pelo PostgreSQL?
##### Heap
É o formato padrão de armazenamento de tabelas no PostgreSQL, cada tabela é guardada em arquivos segmentados no diretório PGDATA/base/(diretorio de armazenamento), por default, os blocos da heap são de 8KB.
##### Sequencial
O PostgreSQL armazena os dados da forma que são inseridos, não havendo ordenação, porém há um comando de varredura que faz uma leitura ordenada dos dados, porém não ordena fisicamente os blocos na memória. O comando em questão é `Seq Scan`.
##### Hashing
Como falado anteriormente, o formato padrão de armazenamento é por `heap files`. Para usar o `hashing` no postgreSQL(de forma similar), ele é feito através de index do tipo `hash`. Índices são estruturas de dados extras que auxiliam nas buscas no banco de dados, quando é usado o tipo `hash`, ele cria nessa estrutura de dados uma região de armazenamento, que são chamados `buckets`, onde são guardados as entradas que têm o mesmo valor de `hash` gerado pelas função `hash`. Por exemplo, passamos uma chave para a função, a função vai retornar um número, e esse número é mapeado para um `bucket`, o PostgreSQL armazena os ponteiros para as tuplas da `heap` que correspondem ao valor gerado pela função `hash` anteriormente.
##### Clustering
Como falado anteriormente, o formato padrão de armazenamento é por `heap files`, mas é possível organizar os blocos de forma física no formato `clustering`, no entanto, isso não é mantido automaticamente, é necessário, constantemente, executar o comando `CLUSTER` para fazer a organização.
#### 3. Faça a documentação inicial do Projeto Físico da "Seguradora" definindo tipo de dados, tipo de arquivos e tamanho dos registros.
##### Clientes

| Identificador | Cliente                                                            |
| ------------- | ------------------------------------------------------------------ |
| Descrição     | Tabela de armazenamento de todos os clientes da empresa Seguradora |
| Organização   | Tabela Heap                                                        |
| Ordenação     | id_cliente                                                         |
- Atributos

| Nome     | Chave    | Tipo de dados | Tamanho | Restrições              | Bytes |
| -------- | -------- | ------------- | ------- | ----------------------- | ----- |
| id       | Primária | Serial        | -       | Not Null, Sem repetição | 4     |
| numero   | -        | Varchar       | 30      | Not null                | 30    |
| nome     | -        | Varchar       | 150     | Not null                | 150   |
| endereco | -        | Varchar       | 200     | Not null                | 200   |
##### Carros

| Identificador | Carros                                                              |
| ------------- | ------------------------------------------------------------------- |
| Descrição     | Tabela de armazenamento de todos os carros relacionados às apólices |
| Organização   | Tabela Heap                                                         |
| Ordenação     | id                                                                  |
- Atributos

| Nome     | Chave    | Tipo de dados | Tamanho | Restrições              | Bytes |
| -------- | -------- | ------------- | ------- | ----------------------- | ----- |
| id       | Primária | Serial        | -       | Not Null, Sem repetição | 4     |
| registro | -        | Varchar       | 200     | Not null                | 200   |
| marca    | -        | Varchar       | 150     | Not null                | 50    |
##### Acidentes

| Identificador | Acidentes                                                          |
| ------------- | ------------------------------------------------------------------ |
| Descrição     | Tabela de armazenamento de todos acidentes relacionados aos carros |
| Organização   | Tabela Heap                                                        |
| Ordenação     | id                                                                 |
- Atributos

| Nome     | Chave       | Tipo de dados | Tamanho | Restrições                  | Bytes |
| -------- | ----------- | ------------- | ------- | --------------------------- | ----- |
| id       | Primária    | Serial        | -       | Not Null, Sem repetição     | 4     |
| local    | -           | Varchar       | 100     | Not null                    | 100   |
| data     | -           | Varchar       | -       | Not null                    | 8     |
| id_carro | Estrangeira | Integer       | -       | Chave estrangeira, not null | 4     |

##### Apólices

| Identificador | Apólices                                                            |
| ------------- | ------------------------------------------------------------------- |
| Descrição     | Tabela de armazenamento de todos apólices relacionados aos clientes |
| Organização   | Tabela Heap                                                         |
| Ordenação     | id                                                                  |
- Atributos

| Nome       | Chave       | Tipo de dados | Tamanho | Restrições                  | Bytes |
| ---------- | ----------- | ------------- | ------- | --------------------------- | ----- |
| id         | Primária    | Serial        | -       | Not Null, Sem repetição     | 4     |
| numero     | -           | Varchar       | 100     | Not null                    | 100   |
| id_cliente | Estrangeira | Integer       | -       | Chave estrangeira, not null | 4     |
| id_carro   | Estrangeira | Integer       | -       | Chave estrangeira, not null | 4     |
|            |             |               |         |                             |       |
|            |             |               |         |                             |       |
|            |             |               |         |                             |       |
|            |             |               |         |                             |       |
#### 4. Mostre seu script SQL da criação das tabelas e definições de dados.
```sql
CREATE TABLE IF NOT EXISTS Clientes(
	id SERIAL PRIMARY KEY,
	numero VARCHAR(30) NOT NULL,
	nome VARCHAR(150) NOT NULL,
	endereco VARCHAR(200) NOT NULL
);

CREATE TABLE IF NOT EXISTS Carros(
	id SERIAL PRIMARY KEY,
	registro VARCHAR(200) NOT NULL,
	marcar VARCHAR(50) NOT NULL
);

CREATE TABLE IF NOT EXISTS Acidentes(
	id SERIAL PRIMARY KEY,
	local VARCHAR(100) NOT NULL,
	data TIMESTAMP NOT NULL,
	id_carro INT, 
	CONSTRAINT fk_idcarro FOREIGN KEY(id_carro) REFERENCES Carros(id)
);

CREATE TABLE IF NOT EXISTS Apolices(
	id SERIAL PRIMARY KEY,
	numero VARCHAR(30) NOT NULL,
	id_cliente INT,
	id_carro INT, 
	CONSTRAINT fk_idcliente FOREIGN KEY(id_cliente) REFERENCES Clientes(id),
	CONSTRAINT fk_idcarro FOREIGN KEY(id_carro) REFERENCES Carros(id)
);
```