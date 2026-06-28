#include <stdio.h>
#include "arquivo.h"

void salvarCSV(){
    if(totalEstacoes == 0){
        printf("Nenhuma estacao cadastrada para salvar.\n");
        printf("\nPressione Enter para continuar...\n");
        getchar();
        return;
    }
    FILE *arquivo = fopen("estacoes.csv", "w");
    if(arquivo == NULL){
        printf("Erro ao abrir arquivo.\n");
        printf("\nPressione Enter para continuar...\n");
        getchar();
        return;
    }   
    fprintf(arquivo, "ID,Nome,Operador,Sensor,Data,N,Media,Variancia,DesvioPadrao,Leituras\n");
    for(int i = 0; i< totalEstacoes; i ++){
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
        for(int j = 0; j < estacoes[i].n; j++){
            fprintf(arquivo, "%.2f", estacoes[i].leituras[j]);
            if(j < estacoes[i].n - 1) fprintf(arquivo, ";");
        }
            fprintf(arquivo, "\n"); // pula linha para próxima estação
    }
    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
    printf("\nPressione Enter para continuar...\n");
    getchar();
}


void carregarCSV(){

}