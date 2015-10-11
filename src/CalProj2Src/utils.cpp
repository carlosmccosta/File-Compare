/**\file utils.cpp
 * \brief namespace com uma biblioteca de funções usadas na interface com o utilizador.
 *
 * @version CAL1011_2MIEIC6_8_TG2_1 - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */


#include "utils.h"


/**
 * \brief Limpa as flags do cin e fica à espera de um input para prosseguir.
 * \details Serve para parar o programa e esperar que o utilizador faça algum input para prosseguir.
 *          Evita user system("pause"), que não é portable, não é standard e é muito mais "pesado" para o programa...
 */
void utils::getUserInput() {
	cout << "Prima ENTER para continuar..." << endl;

	//Limpa as flags do cin
	cin.clear();

	cin.sync(); // http://www.cplusplus.com/forum/beginner/1988/page5.html

	//String temporária para guardar os dados lidos
	string temp;

	//Obtenção de uma linha de input para continuar
	getline(cin, temp);

	cin.clear();
	cin.sync();
}


/**
 * getline que faz o sync para não ler lixo do buffer.
 * @return Retorna a string com a linha lida do cin.
 */
string utils::getlineCin() {
	cin.clear();
	cin.sync();

	string input;
#ifdef USE_NCURSES
	char buff[256];
	getnstr(buff, 256);
	input = (string)buff;
#else
	getline(cin, input);
#endif
	cin.clear();
	cin.sync();

	return input;
}


/**
 * Método que limpa o ecrã da consola.
 * Evita usar system("cls"), que não é portable, não é standard e é muito mais "pesado" para o programa...
 */
void utils::clearConsoleScreen() {
	for (size_t i = 0; i < 80; ++i) {
		cout << "\n";
	}

	cout << endl;
}


/**
 * \brief Mostra a "message" ao utilizador e espera por um input de um número entre min (default é 0) e size-1 (default é INT_MAX).
 * \details Enquanto não for introduzido um input válido vai pedindo ao utilizador para introduzir novamente os dados mostrando a errorMessage.
 */
int utils::getIntCin(const char* message, const char* errorMessage, int min, int size) {

	int numero;
	do {
		cout << message;

		/*
		 * Enquanto cin devolver um apontador NULL (e como tal no teste do if dar true (por estar negado)),
		 * devido ao facto de estar a ler dados que não são números, (ex: caracteres...)
		 * informa ao utilizador que tem que introduzir um nº e pede para introduzir os dados novamente.
		 */
		if (!(cin >> numero)) {

			//Limpa as flags do cin
			cin.clear();

			//Extrai e ignora todos os caracteres que estavam no buffer de cin, visto que ao tentar-se introduzir
			//caracteres num int (por ex), o cin entra em estado de erro e não remove os caracteres que leu do buffer
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << errorMessage << endl;
		} else {

			//Testa se os números introduzidos estão dentro do intervalo pedido
			if (numero >= min && numero < size)
				break; //Se estiverem sai-se do loop
			else
				cout << errorMessage << endl; //Senão informasse o utilizador e pede-se novamente o nº
		}

	} while (true);

	cin.clear();
	cin.sync();

	return numero;
}


/**
 * Método que pede ao utilizador uma resposta booleana, esperando que este introduza 'S' ou 'N'
 * @param message mensagem a mostrar antes de pedir o input
 * @param message_erro mensagem a mostrar caso o usar introduza uma letra diferente de 'S' ou 'N'
 * @return true caso o user tenha introduzido S ou false caso tenha introduzido N
 */
bool utils::getYesNoCin(const char* message, const char* message_erro)
{
	bool continuar = false;

	//Pergunta ao utilizador se quer continuar (S/N)
	bool opcao_incorrecta;
	string opcao;

	do {
		cout << message;

		opcao = getlineCin();
		if ((opcao == "S") || (opcao == "s")) {
			continuar = true;
			opcao_incorrecta = false;
		}
		else if ((opcao == "N") || (opcao == "n")) {
			continuar = false;
			opcao_incorrecta = false;
		}
		else {
			cout << message_erro;
			opcao_incorrecta = true;
		}
	} while (opcao_incorrecta);

	cin.clear();
	cin.sync();

	return continuar;
}


/**
 * Método que obtêm o nome de um ficheiro válido para input ou output
 * @param message mensagem a mostrar antes de pedir o input
 * @param message_erro mensagem a mostrar caso o usar introduza input inválido
 * @param inputFile flag que indica que será lido um ficheiro para input (true) ou para output (false)
 * @return O nome do ficheiro lido
 */
string utils::getFileNameCin(const char* message, const char* message_erro, bool inputFile) {
	string filename;
	bool invalidName = true;

	do {
		cout << message;
		filename = utils::getlineCin();

		if (inputFile) {
			if (checkIfFileExists(filename)) {
				invalidName = false;
			} else {
				cout << message_erro;
				invalidName = true;
			}
		} else {
			if (checkIfFileExists(filename)) {
				cout << message_erro;
				invalidName = !getYesNoCin("\nPretende fazer overwrite ao ficheiro (S/N)? : ", "Introduza S para fazer overwrite, ou nao para introduzir outro nome!\n");
			} else {
				invalidName = false;
			}
		}


	} while (invalidName);


	return filename;
}


/**
 * Método que verifica se um ficheiro existe
 * @param filename Nome do ficheiro a verificar
 * @return true caso exista
 */
bool utils::checkIfFileExists(string filename) {
	ifstream inputFileStream(filename.c_str());
	if (inputFileStream.is_open()) {
		inputFileStream.close();
		return true;
	} else {
		return false;
	}
}


/**
 * Método que converte uma string para maiúsculas
 * @param str string a converter
 * @return string convertida
 */
string utils::toUpper(string str) {
	for (string::size_type i = 0; i < str.size(); i++) {
		str[i] = toupper(str[i]);
	}

	return str;
}


/**
 * Método que converte uma string para minúsculas
 * @param str string a converter
 * @return string convertida
 */
string utils::toLower(string str) {
	for (string::size_type i = 0; i < str.size(); i++) {
		str[i] = tolower(str[i]);
	}

	return str;
}

