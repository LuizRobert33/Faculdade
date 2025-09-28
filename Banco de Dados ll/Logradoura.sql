--  tabela Cliente
CREATE TABLE Cliente (
    numero INT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL
);

--  tabela Logradouro
CREATE TABLE Logradouro (
    numero INT PRIMARY KEY,
    data DATE,
    cliente_numero INT NOT NULL,
    FOREIGN KEY (cliente_numero) REFERENCES Cliente(numero)
);

--  tabela Carro
CREATE TABLE Carro (
    numero INT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    modelo VARCHAR(100),
    logradouro_numero INT UNIQUE,  -- 1:1 com logradouro
    FOREIGN KEY (logradouro_numero) REFERENCES Logradouro(numero)
);

--  tabela Acidente
CREATE TABLE Acidente (
    id_acidente INT PRIMARY KEY AUTO_INCREMENT,
    data DATE,
    hora TIME,
    local VARCHAR(200),
    carro_numero INT,
    FOREIGN KEY (carro_numero) REFERENCES Carro(numero)
);
