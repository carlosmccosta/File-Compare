/**\file ConsoleControl.cpp
 * \brief Implementação da classe ConsoleControl
 *
 * @version CAL1011_2MIEIC6_8_TG2_1 - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */

#include "ConsoleControl.h"


#ifdef __linux__
/// Método que inicializa o Ncurses
void ConsoleControl::initNCursers() {
    initscr();      /* Esta função  inicializa a ncurses. Para todos os programas devemos
                       sempre inicializar a ncurses e depois finalizar, como veremos adiante. */

    start_color(); //Esta função torna possível o uso das cores

    //Abaixo estamos definindo os pares de cores que serão utilizados no programa
    init_pair(1,COLOR_WHITE,COLOR_BLACK);
    init_pair(2,COLOR_GREEN,COLOR_BLACK);
    init_pair(3,COLOR_RED,COLOR_BLACK);
    init_pair(4,COLOR_YELLOW,COLOR_BLUE);
    init_pair(5,COLOR_YELLOW,COLOR_BLACK);
    init_pair(6,COLOR_GREEN,COLOR_CYAN);
    init_pair(7,COLOR_RED,COLOR_CYAN);
    init_pair(8,COLOR_YELLOW,COLOR_CYAN);
    init_pair(9,COLOR_WHITE,COLOR_CYAN);

    bkgd(COLOR_PAIR(1));        /*Aqui nós definiremos que a cor de fundo do nosso
                                  programa será azul e a cor dos textos será branca.*/
}
#endif



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <métodos de manipulação da consola>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Método que altera a cor do texto e do fundo da consola
 * @param textColor cor a dar ao testo (Windows API)
 * @param backGroundColor cor a dar ao backGround (Windows API)
 * @param colorPair par de cores para o texto e backGround (Ncurses)
 */
void ConsoleControl::setConsoleTextAndBackGroundColor(int textColor, int backGroundColor, int colorPair) {
#ifdef __linux__
	attron(COLOR_PAIR(colorPair));
#else
	setTextColor(textColor);
	setTextBackground(backGroundColor);
#endif
}


/// Método que faz o reset às cores da consola (texto branco / cinzento e fundo preto)
void ConsoleControl::resetConsoleColors() {
#ifdef __linux__
	attron(COLOR_PAIR(1));
#else
	setTextColor(LGREY);
	setTextBackground(BLACK);
#endif
}


/**
 * Método que mostra uma string na consola com as cores dadas
 * @param str string a mostrar
 * @param textColor cor a dar ao texto (Windows API)
 * @param backGroundColor cor a dar ao fundo (Windows API)
 * @param colorPair par de cores texto/fundo (Ncurses)
 */
void ConsoleControl::showString(string str, int textColor, int backGroundColor, int colorPair) {
	setConsoleTextAndBackGroundColor(textColor, backGroundColor, colorPair);

#ifdef __linux__
	printw(str.c_str());
#else
	cout << str;
#endif

	resetConsoleColors();
}


/**
 * Método que mostra um caracter na consola com as cores fornecidas
 * @param character caracter a mostrar na consola
 * @param textColor cor do texto (Windows API)
 * @param backGroundColor cor do fundo (Windows API)
 * @param colorPair par de cores texto/fundo (Ncurses)
 */
void ConsoleControl::showChar(char character, int textColor, int backGroundColor, int colorPair) {
	setConsoleTextAndBackGroundColor(textColor, backGroundColor, colorPair);

#ifdef __linux__
	printw(&character);
#else
	cout << character;
#endif

	resetConsoleColors();
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </métodos de manipulação da consola>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <métodos para mostar o conteudo do Diff>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Método que mostra uma linha que é comum nos dois ficheiros analisados (com cores)
 * @param line linha a mostrar
 */
void ConsoleControl::showEqualLine(string line) {
	showString(line, GREY, BLACK, 1);
	cout << endl;
}


/**
 * Método que mostra uma linha que foi inserida no ficheiro modificado (com cores)
 * @param line linha a mostrar
 */
void ConsoleControl::showInsertedLine(string line) {
	showString(line, GREEN, BLACK, 2);
	cout << endl;
}

/**
 * Método que mostra uma linha que foi eliminada no ficheiro modificado (com cores)
 * @param line linha a mostrar
 */
void ConsoleControl::showDeletedLine(string line) {
	showString(line, RED, BLACK, 3);
	cout << endl;
}


/**
 * Método que mostra uma linha que foi movida no ficheiro modificado (com cores)
 * @param line linha a mostrar
 */
void ConsoleControl::showMovedLine(string line) {
	showString(line, YELLOW, BLUE, 4);
	cout << endl;
}

/**
 * Método que mostra uma linha que foi alterada no ficheiro modificado (com cores)
 * @param line linha a mostrar
 */
void ConsoleControl::showChangedLine(string line) {
	showString(line, YELLOW, BLACK, 5);
	cout << endl;
}

/**
 * Método que mostra uma linha que se manteve igual nos dois ficheiros (com cores)
 * @param line linha a mostrar
 */
void ConsoleControl::showUnChangedLine(string line) {
	showString(line, WHITE, BLACK, 1);
	cout << endl;
}



/**
 * Método que mostra um caracter que foi inserido no ficheiro modificado (com cores)
 * @param character caracter a mostrar
 */
void ConsoleControl::showInsertedChar(char character) {
	showChar(character, GREEN, BLACK, 2);
}

/**
 * Método que mostra um caracter que foi eliminado no ficheiro modificado (com cores)
 * @param character caracter a mostrar
 */
void ConsoleControl::showDeletedChar(char character) {
	showChar(character, RED, BLACK, 3);
}

/**
 * Método que mostra um caracter que foi alterado no ficheiro modificado (com cores)
 * @param character caracter a mostrar
 */
void ConsoleControl::showChangedChar(char character) {
	showChar(character, YELLOW, BLACK, 5);
}

/**
 * Método que mostra um caracter que se manteve inalterado nos dois ficheiros (com cores)
 * @param character caracter a mostrar
 */
void ConsoleControl::showUnChangedChar(char character) {
	showChar(character, WHITE, BLACK, 1);
}




/**
 * Método que mostra um caracter que foi inserido e movido numa linha que alterou de posição no ficheiro modificado (com cores)
 * @param character caracter a mostrar
 */
void ConsoleControl::showInsertedAndMovedChar(char character) {
	showChar(character, GREEN, BROWN, 6);
}

/**
 * Método que mostra um caracter que foi eliminado e movido numa linha que alterou de posição no ficheiro modificado (com cores)
 * @param character caracter a mostrar
 */
void ConsoleControl::showDeletedAndMovedChar(char character) {
	showChar(character, RED, BROWN, 7);
}

/**
 * Método que mostra um caracter que foi alterado e movido numa linha que alterou de posição no ficheiro modificado (com cores)
 * @param character caracter a mostrar
 */
void ConsoleControl::showChangedAndMovedChar(char character) {
	showChar(character, LIMEG, BROWN, 8);
}

/**
 * Método que mostra um caracter que que se manteve inalterado numa linha que mudou de posição no ficheiro modificado (com cores)
 * @param character caracter a mostrar
 */
void ConsoleControl::showUnChangedAndMovedChar(char character) {
	showChar(character, WHITE, BROWN, 9);
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </métodos para mostar o conteudo do Diff>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
