#ifndef DEFS_H_
#define DEFS_H_

/**\file defs.h
 * \brief Ficheiro com as definições do programa.
 *
 * @version CAL1011_2MIEIC6_8_TG2_1 - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */


//#define DEBUG 1
//#define USE_NCURSES 1

/**
 * Para ajustar o quanto as strings têm que ser semelhantes para serem consideradas como semelhantes
 * (ou seja, que correspondem a uma mesma linha de texto, que poderá ter sido movida de posição nos ficheiros),
 * é usado o
 * #define PERCENTAGE_TO_CONSIDER_DIFERENTE_LINE 0.66
 * Que define qual o tamanho de edição mínimo que as strings a comparar têm que ter para serem consideras semelhantes.
 * Ou seja, quando mais próximo de 1 mais tolerante ao tamanho de edição o algoritmo é
 */
#define PERCENTAGE_TO_CONSIDER_DIFERENTE_LINE 0.66

#define LINE_NOT_MOVED_INDEX -1




#endif /* DEFS_H_ */
