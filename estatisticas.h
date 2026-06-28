#ifndef ESTATISTICAS_H //garante que o arquivo vai ser lido so uma vez
#define ESTATISTICAS_H

#include "estacao.h"

/*
 * arquivo: estatisticas.h
 * descricao: declaracao dos prototipos das funcoes de calculo
 *             estatistico — media recursiva, variancia e desvio padrao.
 */

float somaRecursiva(float *leituras, int n);
float calcularMedia(float *leituras, int n);
float calcularVariancia(float *leituras, int n, float media);
float calcularDesvioPadrao(float variancia);

#endif