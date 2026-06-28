#include <stdio.h>
#include <stdlib.h>
#include "estacao.h"
#include "arquivo.h"

/*
 * arquivo: main.c
 * descricao: ponto de entrada do programa. Exibe o menu principal
 *             e gerencia o fluxo de opcoes do usuario.
 * autor: Davi Eduardo 
 * data: 2026
 */

int main(){
    printf("=====================================\n");
    printf("  Sistema de Monitoramento Meteorologico\n");
    printf("=====================================\n");
    
    int opcao = 0;
    do
    {
        printf("1-Cadastrar estacao\n2-Editar estacao\n3-Remover estacao\n4-Listar estacoes\n5-Buscar por operador\n6-Detectar anomalias\n7-Salvar CSV\n8-Carregar CSV\n0-Sair\n");
        scanf("%d", &opcao);
        while (getchar() != '\n')
            ; // limpa o buffer
        switch (opcao)
        {
        case 1:
            adicionarEstacao();
            break;
        case 2:
            editarEstacao();
            break;
        case 3:
            removerEstacao();
            break;
        case 4:
            listarEstacoes();
            break;
        case 5:
            buscarPorOperador();
            break;
        case 6:
            detectarAnomalias();
            break;
        case 7:
            salvarCSV();
            break;
        case 8:
            carregarCSV();
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida\n");
            break;
        }

    } while (opcao != 0);
}