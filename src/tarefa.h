
/*
recebe i, a linha e coluna em cima de onde calcular o PI e referencias para o maior e menor elemento
retorna o valor do PI e, por referencia os valores do maior e menor elemento
*/
int produtoInternoEMaiorMenorElementoParcial(int i, int* maiorElem, int* menorElem);

/*
recebe vetor contendo os indices das linhas/colunas das quais
ira calcular os PIs
retorna por referencia mediaPI, media Parcial dos PIs, mediaQuadradoPI,
media parcial dos quadrados dos PIs usado no calculo do desvio padrao,
meiorElem, maior elemento parcial da matriz gerada,
menorElem, menor elemento parcial da matriz gerada,
maiorPI, maior PI parcial,
menorPI, menor PI parcial
*/
void executaTarefa(int* indices, int tamVetorIndices, float* mediaPI, float* mediaQuadradoPI, int* maiorElem, int* menorElem, int* maiorPI, int* menorPI);

