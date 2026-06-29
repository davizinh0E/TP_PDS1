#ifndef ESTACAO_H
#define ESTACAO_H
#define MAX_ESTACOES 100

/*
 * arquivo: estacao.h
 * descricao: declaracao das structs e prototipos das funcoes
 *             de gerenciamento de estacoes meteorologicas.
 */

struct DataLeitura
{
    int dia;
    int mes;
    int ano;
};

struct Estacao
{
    int id;
    char nome[40];
    char operador[40];
    char sensor[20]; // Temperatura, umidade, pressão.
    int n;           // Quantidade de leituras
    float *leituras; // Vetor alocado dinâmicamente
    float media;
    float variancia;
    float desvioPadrao;
    struct DataLeitura data; // Data da coleta
};

extern struct Estacao estacoes[MAX_ESTACOES]; //podem ser acessadar por qualquer arquivo da pasta
extern int totalEstacoes;
extern int contador; // contador de ids

void adicionarEstacao();
void listarEstacoes();
void buscarPorOperador();
void removerEstacao();
void editarEstacao();
void detectarAnomalias();

#endif