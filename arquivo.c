#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"

/*
 * funcao: salvarCSV
 * descricao: grava todas as estacoes cadastradas em um arquivo CSV,
 *             incluindo todas as leituras separadas por ponto e virgula.
 * retorno: void
 */
void salvarCSV()
{
    if (totalEstacoes == 0)
    {
        printf("Nenhuma estacao cadastrada para salvar.\n");
        printf("\nPressione Enter para continuar...\n");
        getchar();
        return;
    }
    FILE *arquivo = fopen("estacoes.csv", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
        printf("\nPressione Enter para continuar...\n");
        getchar();
        return;
    }
    fprintf(arquivo, "ID,Nome,Operador,Sensor,Data,N,Media,Variancia,DesvioPadrao,Leituras\n");
    for (int i = 0; i < totalEstacoes; i++)
    {
        fprintf(arquivo, "%d,%s,%s,%s,%d/%d/%d,%d,%.2f,%.2f,%.2f,",
                estacoes[i].id,
                estacoes[i].nome,
                estacoes[i].operador,
                estacoes[i].sensor,
                estacoes[i].data.dia,
                estacoes[i].data.mes,
                estacoes[i].data.ano,
                estacoes[i].n,
                estacoes[i].media,
                estacoes[i].variancia,
                estacoes[i].desvioPadrao);
        for (int j = 0; j < estacoes[i].n; j++)
        {
            fprintf(arquivo, "%.2f", estacoes[i].leituras[j]);
            if (j < estacoes[i].n - 1)
                fprintf(arquivo, ";");
        }
        fprintf(arquivo, "\n"); // pula linha para próxima estação
    }
    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
    printf("\nPressione Enter para continuar...\n");
    getchar();
}


/*
 * funcao: carregarCSV
 * descricao: le o arquivo CSV e restaura as estacoes para a memoria,
 *             recalculando todos os campos e realocando as leituras.
 * retorno: void
 */
void carregarCSV()
{
    FILE *arquivo = fopen("estacoes.csv", "r");
    if (arquivo == NULL)
    {
        printf("Nenhum arquivo encontrado.\n");
        printf("\nPressione Enter para continuar...\n");
        getchar();
        return;
    }

    char linha[500];

    fgets(linha, 500, arquivo); // lê e descarta o cabeçalho
    while (fgets(linha, 500, arquivo))
    { // lê as estações
        char *token = strtok(linha, ",");
        estacoes[totalEstacoes].id = atoi(token); // converte string para int

        token = strtok(NULL, ","); // continua onde parou
        strcpy(estacoes[totalEstacoes].nome, token);

        token = strtok(NULL, ",");
        strcpy(estacoes[totalEstacoes].operador, token);

        token = strtok(NULL, ",");
        strcpy(estacoes[totalEstacoes].sensor, token);

        token = strtok(NULL, ","); // pega "dd/mm/aaaa"
        estacoes[totalEstacoes].data.dia = atoi(strtok(token, "/"));
        estacoes[totalEstacoes].data.mes = atoi(strtok(NULL, "/"));
        estacoes[totalEstacoes].data.ano = atoi(strtok(NULL, "/"));

        token = strtok(NULL, ",");
        estacoes[totalEstacoes].n = atoi(token);

        token = strtok(NULL, ",");
        estacoes[totalEstacoes].media = atof(token); // converte str para float

        token = strtok(NULL, ",");
        estacoes[totalEstacoes].variancia = atof(token);

        token = strtok(NULL, ",");
        estacoes[totalEstacoes].desvioPadrao = atof(token);

        estacoes[totalEstacoes].leituras = malloc(estacoes[totalEstacoes].n * sizeof(float));
        for (int j = 0; j < estacoes[totalEstacoes].n; j++)
        {
            token = strtok(NULL, ";");
            estacoes[totalEstacoes].leituras[j] = atof(token);
        }

        totalEstacoes++;
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso!\n");
    printf("\nPressione Enter para continuar...\n");
    getchar();
}