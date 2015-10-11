#ifndef CONSOLECONTROL_H_
#define CONSOLECONTROL_H_

/**\file ConsoleControl.h
 * \brief Classe que fornece uma API de controlo das cores da console (multiplataforma)
 *
 * @version CAL1011_2MIEIC6_8_TG2_1 - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */


#ifdef __linux__
#include <curses.h>
#include <stdio.h>
#endif


#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;



#include "WinConsole.h"



//############################################################   ConsoleControl   ##################################################################
/**
 * Classe que fornece uma API de controlo das cores da console (multiplataforma)
 */
namespace ConsoleControl {

#ifdef __linux__
/// Método que inicializa o Ncurses
void initNCursers();
#endif


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <métodos de manipulação da consola>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Método que altera a cor do texto e do fundo da consola
 * @param textColor cor a dar ao testo (Windows API)
 * @param backGroundColor cor a dar ao backGround (Windows API)
 * @param colorPair par de cores para o texto e backGround (Ncurses)
 */
void setConsoleTextAndBackGroundColor(int textColor, int backGroundColor, int colorPair);

/// Método que faz o reset às cores da consola (texto branco / cinzento e fundo preto)
void resetConsoleColors();

/**
 * Método que mostra uma string na consola com as cores dadas
 * @param str string a mostrar
 * @param textColor cor a dar ao texto
 * @param backGroundColor cor a dar ao fundo
 * @param colorPair par de cores texto/fundo
 */
void showString(string line, int textColor, int backGroundColor, int colorPair);

/**
 * Método que mostra um caracter na consola com as cores fornecidas
 * @param character caracter a mostrar na consola
 * @param textColor cor do texto (Windows API)
 * @param backGroundColor cor do fundo (Windows API)
 * @param colorPair par de cores texto/fundo (Ncurses)
 */
void showChar(char character, int textColor, int backGroundColor, int colorPair);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </métodos de manipulação da consola>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <métodos para mostar o conteudo do Diff>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Método que mostra uma linha que é comum nos dois ficheiros analisados (com cores)
 * @param line linha a mostrar
 */
void showEqualLine(string line);

/**
 * Método que mostra uma linha que foi inserida no ficheiro modificado (com cores)
 * @param line linha a mostrar
 */
void showInsertedLine(string line);

/**
 * Método que mostra uma linha que foi eliminada no ficheiro modificado (com cores)
 * @param line linha a mostrar
 */
void showDeletedLine(string line);

/**
 * Método que mostra uma linha que foi movida no ficheiro modificado (com cores)
 * @param line linha a mostrar
 */
void showMovedLine(string line);

/**
 * Método que mostra uma linha que foi alterada no ficheiro modificado (com cores)
 * @param line linha a mostrar
 */
void showChangedLine(string line);

/**
 * Método que mostra uma linha que se manteve igual nos dois ficheiros (com cores)
 * @param line linha a mostrar
 */
void showUnChangedLine(string line);


/**
 * Método que mostra um caracter que foi inserido no ficheiro modificado (com cores)
 * @param character caracter a mostrar
 */
void showInsertedChar(char character);

/**
 * Método que mostra um caracter que foi eliminado no ficheiro modificado (com cores)
 * @param character caracter a mostrar
 */
void showDeletedChar(char character);

/**
 * Método que mostra um caracter que foi alterado no ficheiro modificado (com cores)
 * @param character caracter a mostrar
 */
void showChangedChar(char character);

/**
 * Método que mostra um caracter que se manteve inalterado nos dois ficheiros (com cores)
 * @param character caracter a mostrar
 */
void showUnChangedChar(char character);



/**
 * Método que mostra um caracter que foi inserido e movido numa linha que alterou de posição no ficheiro modificado (com cores)
 * @param character caracter a mostrar
 */
void showInsertedAndMovedChar(char character);

/**
 * Método que mostra um caracter que foi eliminado e movido numa linha que alterou de posição no ficheiro modificado (com cores)
 * @param character caracter a mostrar
 */
void showDeletedAndMovedChar(char character);

/**
 * Método que mostra um caracter que foi alterado e movido numa linha que alterou de posição no ficheiro modificado (com cores)
 * @param character caracter a mostrar
 */
void showChangedAndMovedChar(char character);

/**
 * Método que mostra um caracter que que se manteve inalterado numa linha que mudou de posição no ficheiro modificado (com cores)
 * @param character caracter a mostrar
 */
void showUnChangedAndMovedChar(char character);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </métodos para mostar o conteudo do Diff>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

}

#endif /* CONSOLECONTROL_H_ */
