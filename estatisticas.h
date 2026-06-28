#ifndef ESTATISTICAS_H //garante que o arquivo vai ser lido so uma vez
#define ESTATISTICAS_H

#include "estacao.h"

float somaRecursiva(float *leituras, int n);
float calcularMedia(float *leituras, int n);
float calcularVariancia(float *leituras, int n, float media);
float calcularDesvioPadrao(float variancia);

#endif