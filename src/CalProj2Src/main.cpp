/**\file main.cpp
 * \brief Ficheiro com a interface com o utilizador.
 *
 * @version CAL1011_2MIEIC6_8_TG2_1 - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */


#include "utils.h"
#include "LCS.h"
#include "EditDistance.h"
#include "Diff.h"
#include "../ConsoleControl/ConsoleControl.h"

#ifdef __linux__
	#include <curses.h>
	#include <stdio.h>
#endif


int main() {

#ifdef __linux__
	ConsoleControl::initNCursers();
#endif


	string originalFilename = utils::getFileNameCin("\n  -> Introduza o nome do ficheiro original: ", "O nome do ficheiro que introduziu nao existe!\n", true);
	string modifiedFilename = utils::getFileNameCin("\n  -> Introduza o nome do ficheiro modificado: ", "O nome do ficheiro que introduziu nao existe!\n", true);
	string patchFilename = utils::getFileNameCin("\n  -> Introduza o nome do ficheiro onde sera guardado o patchFile: ", "O nome do ficheiro que introduziu ja existe!\n", false);

//	string originalFilename = "t1.txt";
//	string modifiedFilename = "t2.txt";
//	string patchFilename = "p.txt";



	Diff* diff = new Diff(originalFilename, modifiedFilename, patchFilename);


	int option = 1;
	do {
		utils::clearConsoleScreen();
		cout << "#########################   CAL - Trabalho 2 - Tema 1   #########################\n";
		cout << "  >>>                        Comparacao de ficheiros                        <<<  \n";
		cout << "#################################################################################\n\n\n";

		cout << " 1 - Comparar ficheiros e criar ficheiro de patch\n";
		cout << " 2 - Mostar ficheiro original\n";
		cout << " 3 - Mostar ficheiro modificado\n";
		cout << " 4 - Carregar ficheiro de patch\n";
		cout << " 5 - Mostrar ficheiro de patch\n\n";
//		cout << " 6 - Mostrar ficheiro original patched\n\n";

		cout << " 6 - Recarregar ficheiros\n";
		cout << " 7 - Mudar ficheiros\n\n";


		cout << " 0 - Sair\n\n\n" << endl;


		option = utils::getIntCin("  >>> Opcao: ", "Introduza uma das opcoes mencionadas em cima!\n", 0, 8);


		switch (option) {
			case 1: {
				diff->showModifiedFileChangesAndCreatePatchCLI();
				break;
			}

			case 2: {
				diff->showOriginalFileCLI();
				break;
			}

			case 3: {
				diff->showModifiedFileCLI();
				break;
			}


			case 4: {
				diff->loadPatchFileCLI();
				break;
			}

			case 5: {
				diff->showPatchFileCLI();
				break;
			}

//			case 6: {
//				diff->showOriginalFilePatchedCLI();
//				break;
//			}

			case 6: {
				delete diff;
				diff = new Diff(originalFilename, modifiedFilename, patchFilename);
				break;
			}

			case 7: {
				delete diff;
				originalFilename = utils::getFileNameCin("\n  -> Introduza o nome do ficheiro original: ", "O nome do ficheiro que introduziu nao existe!\n", true);
				modifiedFilename = utils::getFileNameCin("\n  -> Introduza o nome do ficheiro modificado: ", "O nome do ficheiro que introduziu nao existe!\n", true);
				patchFilename = utils::getFileNameCin("\n  -> Introduza o nome do ficheiro onde sera guardado o patchFile: ", "O nome do ficheiro que introduziu ja existe!\n", false);

				diff = new Diff(originalFilename, modifiedFilename, patchFilename);
				break;
			}

			default:
				break;
			}

	} while (option != 0);




	cout << "\n\n";
	utils::getUserInput();
	ConsoleControl::resetConsoleColors();

#ifdef __linux__
	endwin();
#endif


	return 0;
}
