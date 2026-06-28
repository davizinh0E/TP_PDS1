#include "estacao.h"
#include "estatisticas.h"
#include <math.h>

float somaRecursiva(float *leituras, int n)
{
    if (n == 0)
        return 0; // caso base
    return leituras[n - 1] + somaRecursiva(leituras, n - 1);
}

float calcularMedia(float *leituras, int n)
{
    return somaRecursiva(leituras, n) / n;
}

float calcularVariancia(float *leituras, int n, float media)
{
    float soma = 0;
    for (int i = 0; i < n; i++)
    {
        soma = soma + pow(leituras[i] - media, 2);
    }
    float variancia = soma / n;
    return variancia;
}

float calcularDesvioPadrao(float variancia)
{
    float desvioPadrao = sqrt(variancia);
    return desvioPadrao;
}