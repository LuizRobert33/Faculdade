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