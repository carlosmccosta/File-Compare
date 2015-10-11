/**\file utils.cpp
 * \brief namespace com uma biblioteca de fun��es usadas na interface com o utilizador.
 *
 * @version CAL1011_2MIEIC6_8_TG2_1 - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */


#include "utils.h"


/**
 * \brief Limpa as flags do cin e fica � espera de um input para prosseguir.
 * \details Serve para parar o programa e esperar que o utilizador fa�a algum input para prosseguir.
 *          Evita user system("pause"), que n�o � portable, n�o � standard e � muito mais "pesado" para o programa...
 */
void utils::getUserInput() {
	cout << "Prima ENTER para continuar..." << endl;

	//Limpa as flags do cin
	cin.clear();

	cin.sync(); // http://www.cplusplus.com/forum/beginner/1988/page5.html

	//String tempor�ria para guardar os dados lidos
	string temp;

	//Obten��o de uma linha de input para continuar
	getline(cin, temp);

	cin.clear();
	cin.sync();
}


/**
 * getline que faz o sync para n�o ler lixo do buffer.
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
 * M�todo que limpa o ecr� da consola.
 * Evita usar system("cls"), que n�o � portable, n�o � standard e � muito mais "pesado" para o programa...
 */
void utils::clearConsoleScreen() {
	for (size_t i = 0; i < 80; ++i) {
		cout << "\n";
	}

	cout << endl;
}


/**
 * \brief Mostra a "message" ao utilizador e espera por um input de um n�mero entre min (default � 0) e size-1 (default � INT_MAX).
 * \details Enquanto n�o for introduzido um input v�lido vai pedindo ao utilizador para introduzir novamente os dados mostrando a errorMessage.
 */
int utils::getIntCin(const char* message, const char* errorMessage, int min, int size) {

	int numero;
	do {
		cout << message;

		/*
		 * Enquanto cin devolver um apontador NULL (e como tal no teste do if dar true (por estar negado)),
		 * devido ao facto de estar a ler dados que n�o s�o n�meros, (ex: caracteres...)
		 * informa ao utilizador que tem que introduzir um n� e pede para introduzir os dados novamente.
		 */
		if (!(cin >> numero)) {

			//Limpa as flags do cin
			cin.clear();

			//Extrai e ignora todos os caracteres que estavam no buffer de cin, visto que ao tentar-se introduzir
			//caracteres num int (por ex), o cin entra em estado de erro e n�o remove os caracteres que leu do buffer
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << errorMessage << endl;
		} else {

			//Testa se os n�meros introduzidos est�o dentro do intervalo pedido
			if (numero >= min && numero < size)
				break; //Se estiverem sai-se do loop
			else
				cout << errorMessage << endl; //Sen�o informasse o utilizador e pede-se novamente o n�
		}

	} while (true);

	cin.clear();
	cin.sync();

	return numero;
}


/**
 * M�todo que pede ao utilizador uma resposta booleana, esperando que este introduza 'S' ou 'N'
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
 * M�todo que obt�m o nome de um ficheiro v�lido para input ou output
 * @param message mensagem a mostrar antes de pedir o input
 * @param message_erro mensagem a mostrar caso o usar introduza input inv�lido
 * @param inputFile flag que indica que ser� lido um ficheiro para input (true) ou para output (false)
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
 * M�todo que verifica se um ficheiro existe
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
 * M�todo que converte uma string para mai�sculas
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
 * M�todo que converte uma string para min�sculas
 * @param str string a converter
 * @return string convertida
 */
string utils::toLower(string str) {
	for (string::size_type i = 0; i < str.size(); i++) {
		str[i] = tolower(str[i]);
	}

	return str;
}

