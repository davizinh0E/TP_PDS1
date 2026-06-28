#include "estacao.h"
#include "estatisticas.h"
#include <math.h>

/*
 * funcao: somaRecursiva
 * descricao: calcula a soma dos elementos de um array de floats
 *             recursivamente, usando indice decrescente.
 * parametros: leituras - array de floats, n - quantidade de elementos
 * retorno: float com a soma total
 */
float somaRecursiva(float *leituras, int n)
{
    if (n == 0)
        return 0; // caso base
    return leituras[n - 1] + somaRecursiva(leituras, n - 1);
}


/*
 * funcao: calcularMedia
 * descricao: calcula a media aritmetica das leituras usando somaRecursiva.
 * parametros: leituras - array de floats, n - quantidade de elementos
 * retorno: float com a media
 */
float calcularMedia(float *leituras, int n)
{
    return somaRecursiva(leituras, n) / n;
}


/*
 * funcao: calcularVariancia
 * descricao: calcula a variancia das leituras em relacao a media.
 * parametros: leituras - array de floats, n - quantidade, media - media calculada
 * retorno: float com a variancia
 */
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


/*
 * funcao: calcularDesvioPadrao
 * descricao: calcula o desvio padrao como raiz quadrada da variancia.
 * parametros: variancia - variancia calculada
 * retorno: float com o desvio padrao
 */
float calcularDesvioPadrao(float variancia)
{
    float desvioPadrao = sqrt(variancia);
    return desvioPadrao;
}