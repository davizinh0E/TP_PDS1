#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
    do {
    printf("Mes: ");
    scanf("%d", &estacoes[totalEstacoes].data.mes);
    while(getchar() != '\n');
    if(estacoes[totalEstacoes].data.mes < 1 || estacoes[totalEstacoes].data.mes > 12)
        printf("Mes invalido! Digite um valor entre 1 e 12.\n");
    } while(estacoes[totalEstacoes].data.mes < 1 || estacoes[totalEstacoes].data.mes > 12);
    
    int maxDias;//validacao de dias num mes
    int mes = estacoes[totalEstacoes].data.mes;
    if(mes == 2) maxDias = 29;
    else if(mes == 4 || mes == 6 || mes == 9 || mes == 11) maxDias = 30;
    else maxDias = 31;
    
    do {
    printf("Dia: ");
    scanf("%d", &estacoes[totalEstacoes].data.dia);
    while(getchar() != '\n');
    if(estacoes[totalEstacoes].data.dia < 1 || estacoes[totalEstacoes].data.dia > maxDias){
        printf("Dia invalido! Digite um valor entre 1 e %d.\n", maxDias);
    }
    } while(estacoes[totalEstacoes].data.dia < 1 || estacoes[totalEstacoes].data.dia > maxDias);

    do {
    printf("Ano: ");
    scanf("%d", &estacoes[totalEstacoes].data.ano);
    while(getchar() != '\n');
    if(estacoes[totalEstacoes].data.ano < 1900 || estacoes[totalEstacoes].data.ano > 2100)
        printf("Ano invalido! Digite um valor entre 1900 e 2100.\n");
    } while(estacoes[totalEstacoes].data.ano < 1900 || estacoes[totalEstacoes].data.ano > 2100);

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
        printf("Nao ha estacoes cadastradas.\n");
        printf("\nPressione Enter para continuar...");
        getchar();//para nao voltar no menu automaticamente
        return ;
        }
    for(int i = 0; i < totalEstacoes; i ++){
        printf("Id: %d\nEstacao: %s\nOperador: %s\nSensor: %s\nData:%d/%d/%d\nLeituras: %d\nMedia: %.2f\nVariancia: %.2f\nDesvio Padrao: %.2f\n", estacoes[i].id, estacoes[i].nome, estacoes[i].operador, estacoes[i].sensor, estacoes[i].data.dia, estacoes[i].data.mes, estacoes[i].data.ano, estacoes[i].n, estacoes[i].media, estacoes[i].variancia, estacoes[i].desvioPadrao);   
    }
    printf("\nPressione Enter para continuar...");
    getchar();
}


void buscarPorOperador(){
    char operadorBuscado[40];
    printf("Digite o nome do operador: \n");
    fgets(operadorBuscado, 40, stdin);
    operadorBuscado[strcspn(operadorBuscado, "\n")]= '\0';

    int encontrou = 0;

    for(int i = 0; i < totalEstacoes; i++){
        if(strcmp(estacoes[i].operador, operadorBuscado) == 0){
            printf("Id: %d\nEstacao: %s\nOperador: %s\nSensor: %s\nData:%d/%d/%d\nLeituras: %d\nMedia: %.2f\nVariancia: %.2f\nDesvio Padrao: %.2f\n", estacoes[i].id, estacoes[i].nome, estacoes[i].operador, estacoes[i].sensor, estacoes[i].data.dia, estacoes[i].data.mes, estacoes[i].data.ano, estacoes[i].n, estacoes[i].media, estacoes[i].variancia, estacoes[i].desvioPadrao); 
            encontrou = 1;
        }
    }
    if(encontrou == 0)printf("Operador nao encontrado.\n");

    printf("\nPressione Enter para continuar...\n");
    getchar();
}


void removerEstacao(){
    int idDelete = 0;
    printf("Informe o ID da estacao a ser removida:\n");
    scanf("%d", &idDelete);
    
    for(int i = 0; i<totalEstacoes; i++){
        if(estacoes[i].id == idDelete){
            free(estacoes[i].leituras);
            for(int j = i; j < totalEstacoes-1;j++){
                estacoes[j] = estacoes[j+1];
            }
            totalEstacoes --;
            printf("\nPressione Enter para continuar...\n");
            getchar();
            return;
        }
    }
    printf("Id nao encontrado.");
    printf("\nPressione Enter para continuar...\n");
    getchar();
}


void editarEstacao(){
    int idEdit = 0;
    printf("Informe o ID da estacao a ser modificada:\n");
    scanf("%d", &idEdit);
    while(getchar() != '\n');//nao sair do pressione enter, limpa \n
    
    for(int i = 0; i<totalEstacoes; i++){
        if(estacoes[i].id == idEdit){
            printf("Selecione o parametro a ser editado:\n");
            printf("1-Nome\n2-Operador\n3-Sensor\n4-Data\n");
            int opcao;
            scanf("%d", &opcao);
            while(getchar()!='\n');
            switch (opcao) {
            case 1:
                printf("Novo nome da Estacao: ");
                fgets(estacoes[i].nome, 40, stdin);
                estacoes[i].nome[strcspn(estacoes[i].nome, "\n")] = '\0';;
                break;
            case 2:
                printf("Novo nome do Operador Responsavel: ");
                fgets(estacoes[i].operador, 40, stdin);
                estacoes[i].operador[strcspn(estacoes[i].operador, "\n")] = '\0';
                break;
            case 3:
                printf("Novo tipo de sensor (temperatura, humidade, pressao): ");
                fgets(estacoes[i].sensor, 40, stdin);
                estacoes[i].sensor[strcspn(estacoes[i].sensor, "\n")] = '\0';
                break;    
            case 4:
                printf("Informe a data de criacao:\n");    
                do {
                printf("Mes: ");
                scanf("%d", &estacoes[i].data.mes);
                while(getchar() != '\n');
                if(estacoes[i].data.mes < 1 || estacoes[i].data.mes > 12)
                    printf("Mes invalido! Digite um valor entre 1 e 12.\n");
                } while(estacoes[i].data.mes < 1 || estacoes[i].data.mes > 12);
                
                int maxDias;//validacao de dias num mes
                int mes = estacoes[i].data.mes;
                if(mes == 2) maxDias = 29;
                else if(mes == 4 || mes == 6 || mes == 9 || mes == 11) maxDias = 30;
                else maxDias = 31;
                
                do {
                printf("Dia: ");
                scanf("%d", &estacoes[i].data.dia);
                while(getchar() != '\n');
                if(estacoes[i].data.dia < 1 || estacoes[i].data.dia > maxDias){
                    printf("Dia invalido! Digite um valor entre 1 e %d.\n", maxDias);
                }
                } while(estacoes[i].data.dia < 1 || estacoes[i].data.dia > maxDias);

                do {
                printf("Ano: ");
                scanf("%d", &estacoes[i].data.ano);
                while(getchar() != '\n');
                if(estacoes[i].data.ano < 1900 || estacoes[i].data.ano > 2100)
                    printf("Ano invalido! Digite um valor entre 1900 e 2100.\n");
                } while(estacoes[i].data.ano < 1900 || estacoes[i].data.ano > 2100);
                break;
            default:
                printf("Opção invalida\n");
                break;
            }
            printf("Edicao realizada com sucesso.");
            printf("\nPressione Enter para continuar...\n");
            getchar();
            return;
        }
    }
    printf("Id nao encontrado.");
    printf("\nPressione Enter para continuar...\n");
    getchar();
}


void detectarAnomalias(){
    int idAnomalia = 0;
    printf("Informe o ID da estacao a ser estudada:\n");
    scanf("%d", &idAnomalia);
    while(getchar() != '\n');

    for(int i = 0; i < totalEstacoes ; i++){
        if (estacoes[i].id == idAnomalia){
            int encontrou = 0;
            for(int j = 0; j < estacoes[i].n; j++){
                if(fabs(estacoes[i].leituras[j] - estacoes[i].media) > 2 * estacoes[i].desvioPadrao){
                    printf("Leitura anomala: %.2f\n", estacoes[i].leituras[j]);
                    encontrou = 1;
                }
            }
            if(encontrou == 0) printf("Nenhuma anomalia encontrada.\n");
            printf("\nPressione Enter para continuar...\n");
            getchar();
            return;
        }
    }
    printf("id nao encontrado.");
    printf("\nPressione Enter para continuar...\n");
    getchar();
}