#ifndef DEFS_H_
#define DEFS_H_

/**\file defs.h
 * \brief Ficheiro com as defini��es do programa.
 *
 * @version CAL1011_2MIEIC6_8_TG2_1 - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */


//#define DEBUG 1
//#define USE_NCURSES 1

/**
 * Para ajustar o quanto as strings t�m que ser semelhantes para serem consideradas como semelhantes
 * (ou seja, que correspondem a uma mesma linha de texto, que poder� ter sido movida de posi��o nos ficheiros),
 * � usado o
 * #define PERCENTAGE_TO_CONSIDER_DIFERENTE_LINE 0.66
 * Que define qual o tamanho de edi��o m�nimo que as strings a comparar t�m que ter para serem consideras semelhantes.
 * Ou seja, quando mais pr�ximo de 1 mais tolerante ao tamanho de edi��o o algoritmo �
 */
#define PERCENTAGE_TO_CONSIDER_DIFERENTE_LINE 0.66

#define LINE_NOT_MOVED_INDEX -1




#endif /* DEFS_H_ */
