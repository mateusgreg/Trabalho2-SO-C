/* Disciplina: Sistemas Operacionais I */
/* Prof.: Antonio Thomé */
/* Trabalho: Nr 2 */
/* Autores: João Paulo Ramirez, Jonas Tomaz e Mateus Gregório */

/* Descrição: API Pública do Módulo Concorrente utilizando Subprocessos. */


#include "resultado.h"

/*recebe nsubprocessos o numero de subprocessos
que devem ser criados para a execucao da tarefa
e retorna o resultado calculado pelos subprocessos
*/
Resultado* subprocessos(int nsubprocessos, int k, int* PIFInal);


/*funcao que cada subprocesso vai realmente executar.
Eh a "run" dos subprocessos. ela deve preparar variaveis locais para
os calculos realizados pela executa tarefa e deve colocar esses
resultados nas posicoes corretas dos vetores para a main poder
realizar o calculo final
*/
void executaTarefaSubprocesso(int meuPidLogico);
