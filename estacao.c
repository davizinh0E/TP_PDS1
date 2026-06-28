#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estacao.h"
#include "estatisticas.h"

int totalEstacoes = 0;
int contador = 0;
struct Estacao estacoes[MAX_ESTACOES];

void adicionarEstacao(){
    if(totalEstacoes == MAX_ESTACOES){
        printf("Sistema cheio!\n");
        return;
    }

    estacoes[totalEstacoes].id = contador; //atribui o id atual
    contador ++; //prepara o próximo id

    printf("Nome da Estacao: ");
    fgets(estacoes[totalEstacoes].nome, 40, stdin);
    estacoes[totalEstacoes].nome[strcspn(estacoes[totalEstacoes].nome, "\n")] = '\0'; // remove qualquer \n que possa ser adicionado no nome quando o user clica em enter

    printf("Nome do Operador Responsavel: ");
    fgets(estacoes[totalEstacoes].operador, 40, stdin);
    estacoes[totalEstacoes].operador[strcspn(estacoes[totalEstacoes].operador, "\n")] = '\0';

    printf("Tipo de sensor (temperatura, humidade, pressao): ");
    fgets(estacoes[totalEstacoes].sensor, 40, stdin);
    estacoes[totalEstacoes].sensor[strcspn(estacoes[totalEstacoes].sensor, "\n")] = '\0';

    printf("Informe a data de criacao:\n");
    printf("Dia: ");
    scanf("%d", &estacoes[totalEstacoes].data.dia);
    while(getchar() != '\n'); // limpa o buffer (\n)
    printf("Mes: ");
    scanf("%d", &estacoes[totalEstacoes].data.mes);
    while(getchar() != '\n');
    printf("Ano: ");
    scanf("%d", &estacoes[totalEstacoes].data.ano);
    while(getchar() != '\n'); // limpa o buffer

    printf("Quantidade de Leituras:");
    scanf("%d", &estacoes[totalEstacoes].n);

    estacoes[totalEstacoes].leituras = malloc(estacoes[totalEstacoes].n * sizeof(float));// alocando n valores float
    if(estacoes[totalEstacoes].leituras == NULL){ //teste de memoria disponível
        printf("Erro ao alocar memoria!\n");
        return;
    }
    
    printf("Informe o valor das leituras:\n");
    for(int i =0; i < estacoes[totalEstacoes].n ;i++){
        printf("Leitura %d: ", i+1);
        scanf("%f", &estacoes[totalEstacoes].leituras[i]);
    }

    estacoes[totalEstacoes].media = calcularMedia(estacoes[totalEstacoes].leituras, estacoes[totalEstacoes].n);
    estacoes[totalEstacoes].variancia = calcularVariancia(estacoes[totalEstacoes].leituras, estacoes[totalEstacoes].n, estacoes[totalEstacoes].media);
    estacoes[totalEstacoes].desvioPadrao = calcularDesvioPadrao(estacoes[totalEstacoes].variancia);

    totalEstacoes ++;
}


void listarEstacoes(){
    if(totalEstacoes == 0){
        printf("Nao ha estacoes cadastradas.");
        return ;
        }
    for(int i = 0; i < totalEstacoes; i ++){
        printf("Id: %d\nEstacao: %s\nOperador: %s\nSensor: %s\nData:%d/%d/%d\nLeituras: %d\nMedia: %.2f\nVariancia: %.2f\nDesvio Padrao: %.2f", estacoes[i].id, estacoes[i].nome, estacoes[i].operador, estacoes[i].sensor, estacoes[i].data.dia, estacoes[i].data.mes, estacoes[i].data.ano, estacoes[i].n, estacoes[i].media, estacoes[i].variancia, estacoes[i].desvioPadrao);
    }
}