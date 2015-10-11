/**\file Diff.h
 * \brief Ficheiro com a implementação da classe Diff.
 *
 * @version CAL1011_2MIEIC6_8_TG2_1 - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */


#include "Diff.h"


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/// Default constructor de Diff, que inicializa as estruturas auxiliares
Diff::Diff(string originalFilename, string modifiedFilename, string patchFilename) :
			originalFileName(originalFilename), modifiedFileName(modifiedFilename), patchFileName(patchFilename) {

	//carregamento dos ficheiros
	try {
		loadFile(originalFilename, originalFileData);
		loadFile(modifiedFilename, modifiedFileData);
	} catch (FileDoesntExistException& e) {
		cout << e.what() << "\n" << endl;
		utils::getUserInput();

		originalFileData.clear();
		modifiedFileData.clear();
	}


	//inicialização das estruturas auxiliares
	originalFilePatched = originalFileData;
	originalFilePatchedLinesStatus = vector <LineChangeType>(originalFileData.size(), LINE_EQUAL);

	originalFileLinesStatus = vector <LineInfo>(originalFileData.size(), LineInfo());
	originalFileMovedLinesIndexsInModifiedFile = vector <int>(originalFileData.size(), LINE_NOT_MOVED_INDEX);
	modifiedFileMovedLinesIndexsInOriginalFile = vector <int>(modifiedFileData.size(), LINE_NOT_MOVED_INDEX);
	modifiedFileLinesPresentedOnOriginal = vector <bool>(modifiedFileData.size(), false);


	//análise dos ficheiros
	analyzeFiles();
}


/// Default destructor de Diff
Diff::~Diff() {}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Diff loads-saves>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Método que carrega um ficheiro para um vector de strings
 * Lança excepção FileDoesntExistException se não conseguir abrir o ficheiro
 * @param filename nome do ficheiro a carregar
 * @param fileData vector onde irá guardar os dados
 */
void Diff::loadFile(string filename, vector <string>& fileData) throw(FileDoesntExistException) {
	fileData.clear();

	ifstream inputFileStream(filename.c_str());

	if (inputFileStream.is_open()) {
		while (!inputFileStream.eof()) {
			string temp;
			getline(inputFileStream, temp);
			fileData.push_back(temp);

		}
	} else {
		stringstream ss;
		ss << "O ficheiro com o nome " << filename << " nao existe!\n";
		throw FileDoesntExistException(ss.str().c_str());
	}

}

/**
 * Método que carrega o ficheiro de patch
 * @param filename nome do ficheiro
 */
void Diff::loadPatchFile(string filename) throw(FileDoesntExistException) {
	try {
		loadFile(filename.c_str(), patchFileData);
	} catch (FileDoesntExistException& e) {
		cout << e.what() << "\n\n";

		utils::getUserInput();
	}
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </Diff loads-saves>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Diff analysis algoritms>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/// Método que analiza os 2 ficheiros actualziando as estruturas auxiliares necessárias para fazer o output da diferença entre eles
void Diff::analyzeFiles() {
	findCorrespondentLines();

	for (size_t lineIndex = 0; lineIndex < originalFileLinesStatus.size(); ++lineIndex) {
		LCS lcs;
		string LCSFound;

		if (originalFileLinesStatus[lineIndex].getLinesStatus() == LINE_MODIFIED) {
			lcs = LCS(originalFileData[lineIndex], modifiedFileData[lineIndex]);
			LCSFound = lcs.findLCS();
		}

		if (originalFileLinesStatus[lineIndex].getLinesStatus() == LINE_MOVED_AND_MODIFIED) {
			lcs = LCS(originalFileData[lineIndex], modifiedFileData[originalFileMovedLinesIndexsInModifiedFile[lineIndex]]);
			LCSFound = lcs.findLCS();
		}

		if (LCSFound.empty())
			continue;

		//update aos infos dos chars da linha do ficheiro original
		size_t currentPosOnLCS = 0;
		vector <bool> lineCharsChangedOnOriginalFile(originalFileData[lineIndex].size(), true);
		for (size_t charIndex = 0; charIndex < originalFileData[lineIndex].size(); ++charIndex) {
			if (currentPosOnLCS < LCSFound.size()) {
				if (LCSFound[currentPosOnLCS] == originalFileData[lineIndex][charIndex]) {
					lineCharsChangedOnOriginalFile[charIndex] = false;
					++currentPosOnLCS;
				}
			} else {
				break;
			}
		}

		originalFileLinesStatus[lineIndex].setLineCharsChangedOnOriginalFile(lineCharsChangedOnOriginalFile);



		//update aos infos dos chars da linha do ficheiro modificado
		currentPosOnLCS = 0;
		int indexOfOriginalLineOnModifiedFile = originalFileMovedLinesIndexsInModifiedFile[lineIndex];
		vector <bool> lineCharsChangedOnModifiedFile(modifiedFileData[indexOfOriginalLineOnModifiedFile].size(), true);
		for (size_t charIndex = 0; charIndex < modifiedFileData[indexOfOriginalLineOnModifiedFile].size(); ++charIndex) {
			if (currentPosOnLCS < LCSFound.size()) {
				if (LCSFound[currentPosOnLCS] == modifiedFileData[indexOfOriginalLineOnModifiedFile][charIndex]) {
					lineCharsChangedOnModifiedFile[charIndex] = false;
					++currentPosOnLCS;
				}
			} else {
				break;
			}
		}

		originalFileLinesStatus[lineIndex].setLineCharsChangedOnModifiedFile(lineCharsChangedOnModifiedFile);


	}
}


/// Método que encontra as corrspondências entre linhas que possam ter mudado de posição entre os 2 ficheiros
void Diff::findCorrespondentLines() {
	for (size_t originalTextLineIndex = 0; originalTextLineIndex < originalFileData.size(); ++originalTextLineIndex) {
		int bestMatch = INT_MAX;
		size_t bestMatchLineIndex = 0;
		bool exactMatch = false;


		for (size_t modifiedTextLineIndex = 0; modifiedTextLineIndex < modifiedFileData.size(); ++modifiedTextLineIndex) {
			exactMatch = false;
			EditDistance editDistance(originalFileData[originalTextLineIndex], modifiedFileData[modifiedTextLineIndex]);
			int editDistanceBetweenLines = editDistance.calcEditDistanceOptimized();

			//exact match
			if (editDistanceBetweenLines == 0) {
				//se a linha encontrada ainda não foi associada a outra linha no file original
				if (!modifiedFileLinesPresentedOnOriginal[modifiedTextLineIndex]) {
					exactMatch = true;
					modifiedFileLinesPresentedOnOriginal[modifiedTextLineIndex] = true;

					if (originalTextLineIndex != modifiedTextLineIndex) {
						originalFileLinesStatus[originalTextLineIndex].setLinesStatus(LINE_MOVED);
					} else {
						originalFileLinesStatus[originalTextLineIndex].setLinesStatus(LINE_EQUAL);
					}

					originalFileMovedLinesIndexsInModifiedFile[originalTextLineIndex] = (int)modifiedTextLineIndex;
					modifiedFileMovedLinesIndexsInOriginalFile[modifiedTextLineIndex] = (int)originalTextLineIndex;

					break;
				}
			}

			//aproximate match
			if (editDistanceBetweenLines < (PERCENTAGE_TO_CONSIDER_DIFERENTE_LINE * originalFileData[originalTextLineIndex].size())) {
				if (editDistanceBetweenLines < bestMatch) {
					bestMatch = editDistanceBetweenLines;
					bestMatchLineIndex = modifiedTextLineIndex;
				}
			}
		}

		//se for exact match as actualizações já estão feitas em cima
		if (exactMatch)
			continue;


		//actualizaçao das dados com o melhor match
		if (bestMatch != INT_MAX) {
			//encontrou match
			modifiedFileLinesPresentedOnOriginal[bestMatchLineIndex] = true;

			if (originalTextLineIndex != bestMatchLineIndex) {
				originalFileLinesStatus[originalTextLineIndex].setLinesStatus(LINE_MOVED_AND_MODIFIED);
			} else {
				originalFileLinesStatus[originalTextLineIndex].setLinesStatus(LINE_MODIFIED);
			}

			originalFileMovedLinesIndexsInModifiedFile[originalTextLineIndex] = (int)bestMatchLineIndex;
			modifiedFileMovedLinesIndexsInOriginalFile[bestMatchLineIndex] = (int)originalTextLineIndex;

		} else {
			//não encontrou
			originalFileLinesStatus[originalTextLineIndex].setLinesStatus(LINE_DELETED);
		}
	}
}


/// Método que faz o parse da patchFile de forma a reconstituir o ficheiro modificado a partir do original e de um outro com as diferenças entre os 2
void Diff::parsePatchFile() {
	vector <int> originalIndexs(originalFileData.size(), -1);
	for (size_t i = 0; i < originalIndexs.size(); ++i) {
		originalIndexs[i] = i;
	}

	vector <int> modifiedIndexs = calculateReverseIndexes();


	//parse do patch
	for (size_t i = 0; i < patchFileData.size(); ++i) {
		stringstream sstreamLine(patchFileData[i]);
		string changeType;
		string temp;
		size_t indexFrom;
		size_t indexTo;
		sstreamLine >> changeType;

		if (changeType == (string)"Added") {
			sstreamLine >> temp;
			sstreamLine >> indexTo;
			--indexTo;
			sstreamLine >> temp;
			char buff[256];
			sstreamLine.getline(buff, 256);
			originalFilePatched.insert(originalFilePatched.begin() + modifiedIndexs[indexTo], (string)buff);
			originalFilePatchedLinesStatus.insert(originalFilePatchedLinesStatus.begin() + modifiedIndexs[indexTo], LINE_INSERTED);

			//update indexs
			for (size_t i = indexTo; i < originalIndexs.size(); ++i) {
				++originalIndexs[i];
			}

			for (size_t i = indexTo; i < modifiedIndexs.size(); ++i) {
				++modifiedIndexs[i];
			}

		} else if (changeType == (string)"Deleted") {
			sstreamLine >> temp;
			sstreamLine >> indexTo;
			--indexTo;
			sstreamLine >> temp;
			originalFilePatched.erase(originalFilePatched.begin() + modifiedIndexs[indexTo]);
			originalFilePatchedLinesStatus.erase(originalFilePatchedLinesStatus.begin() + modifiedIndexs[indexTo]);

			//update indexs
			for (size_t i = indexTo+1; i < originalIndexs.size(); ++i) {
				--originalIndexs[i];
			}

			for (size_t i = indexTo+1; i < modifiedIndexs.size(); ++i) {
				--modifiedIndexs[i];
			}

		} else if (changeType == (string)"Modified") {
			sstreamLine >> temp;
			sstreamLine >> indexTo;
			--indexTo;
			sstreamLine >> temp;
			char buff[256];
			sstreamLine.getline(buff, 256);
			originalFilePatched[modifiedIndexs[indexTo]] = (string)buff;
			originalFilePatchedLinesStatus[modifiedIndexs[indexTo]] =  LINE_MODIFIED;

		} else if (changeType == (string)"Moved") {
			sstreamLine >> temp;
			sstreamLine >> indexFrom;
			--indexFrom;
			sstreamLine >> temp;
			sstreamLine >> indexTo;
			--indexTo;
			sstreamLine >> temp;
			char buff[256];
			sstreamLine.getline(buff, 256);
			originalFilePatched.erase(originalFilePatched.begin() + originalIndexs[indexFrom]);
			originalFilePatched.insert(originalFilePatched.begin() + modifiedIndexs[indexTo], (string)buff);
			originalFilePatchedLinesStatus.erase(originalFilePatchedLinesStatus.begin() + originalIndexs[indexFrom]);
			originalFilePatchedLinesStatus.insert(originalFilePatchedLinesStatus.begin() + modifiedIndexs[indexTo], LINE_MOVED);

			//update indexs
			for (size_t i = indexFrom+1; i <= indexTo; ++i) {
				--originalIndexs[i];
			}

			for (size_t i = indexFrom+1; i <= indexTo; ++i) {
				--modifiedIndexs[i];
			}
		}
	}
}

/// Método auxiliar de parsePatchFile que calcula o vector com os indices de destino das modificações na sua forma inversa
vector <int> Diff::calculateReverseIndexes() {
	vector <int> modifiedIndexs(modifiedFileData.size(), -1);
	for (size_t i = 0; i < modifiedIndexs.size(); ++i) {
		modifiedIndexs[i] = i;
	}

	//parse do patch
	for (vector <string>::reverse_iterator it = patchFileData.rbegin(); it != patchFileData.rend(); ++it) {
		stringstream sstreamLine(*it);
		string changeType;
		string temp;
		size_t indexFrom;
		size_t indexTo;
		sstreamLine >> changeType;

		if (changeType == (string)"Added") {
			sstreamLine >> temp;
			sstreamLine >> indexTo;
			--indexTo;

			//update indexs
			for (size_t i = indexTo; i < modifiedIndexs.size(); ++i) {
				--modifiedIndexs[i];
			}


		} else if (changeType == (string)"Deleted") {
			sstreamLine >> temp;
			sstreamLine >> indexTo;
			--indexTo;

			//update indexs
			for (size_t i = indexTo+1; i < modifiedIndexs.size(); ++i) {
				++modifiedIndexs[i];
			}


		} else if (changeType == (string)"Moved") {
			sstreamLine >> temp;
			sstreamLine >> indexFrom;
			--indexFrom;
			sstreamLine >> temp;
			sstreamLine >> indexTo;
			--indexTo;

			//update indexs
			for (size_t i = indexFrom+1; i <= indexTo; ++i) {
				++modifiedIndexs[i];
			}

		}
	}


	return modifiedIndexs;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </Diff analysis algoritms>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Diff console interface>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Método que mostra um ficheiro na interface CLI
 * @param fileData vector de strings com os dados do ficheiro
 */
void Diff::showFileCLI(const vector <string>& fileData) {
	for (size_t i = 0; i < fileData.size(); ++i) {
		cout << fileData[i] << "\n";
	}
}

/// Método que mostra o ficheiro original na interface CLI
void Diff::showOriginalFileCLI() {
	utils::clearConsoleScreen();
	cout << " -------------------------------------------------------------------------------------------\n";
	cout << "|                                 Texto do ficheiro original                                |\n";
	cout << " -------------------------------------------------------------------------------------------\n\n";

	showFileCLI(originalFileData);
	cout << "\n\n";
	utils::getUserInput();
}

/// Método que mostra o ficheiro modificado na interface CLI
void Diff::showModifiedFileCLI() {
	utils::clearConsoleScreen();
	cout << " -------------------------------------------------------------------------------------------\n";
	cout << "|                                Texto do ficheiro modificado                               |\n";
	cout << " -------------------------------------------------------------------------------------------\n\n";

	showFileCLI(modifiedFileData);
	cout << "\n\n";
	utils::getUserInput();
}

/// Método que mostra o ficheiro de patch na interface CLI
void Diff::showPatchFileCLI() {
	utils::clearConsoleScreen();
	cout << " -------------------------------------------------------------------------------------------\n";
	cout << "|                                  Texto do ficheiro de patch                               |\n";
	cout << " -------------------------------------------------------------------------------------------\n\n";

	showFileCLI(patchFileData);
	cout << "\n\n";
	utils::getUserInput();
}


/// Método que mostra na interface CLI as diferenças entre os 2 ficheiros
void Diff::showModifiedFileChangesAndCreatePatchCLI() {
	utils::clearConsoleScreen();
	cout << " -------------------------------------------------------------------------------------------\n";
	cout << " -> Diff entre o ficheiro " << originalFileName << " e " << modifiedFileName << "\n";
	cout << " -------------------------------------------------------------------------------------------\n\n";
	cout << flush;

	ofstream outputFileStream(patchFileName.c_str());

	if (!outputFileStream.is_open()) {
		cerr << "Falha ao criar o ficheiro de patch!" << endl;
		utils::getUserInput();
		return;
	}

	size_t originalFileIndex = 0;
	size_t maxOriginalFileIndex = originalFileData.size();
	size_t modifiedFileIndex = 0;
	size_t maxModifiedFileIndex = modifiedFileData.size();
	int correspondentModifiedIndexInOriginalFile = 0;


	size_t currentIndex = 0;
	while (originalFileIndex < maxOriginalFileIndex || modifiedFileIndex < maxModifiedFileIndex) {
		//*********************************************   insertions on modified file  *******************************************
		if (modifiedFileIndex < maxModifiedFileIndex) {
			if (!modifiedFileLinesPresentedOnOriginal[modifiedFileIndex]) {
				outputFileStream << "Added on " << modifiedFileIndex+1 << " : " << modifiedFileData[modifiedFileIndex] << endl;

				cout << currentIndex+1 << "\t: ";
				cout << "Added on " << modifiedFileIndex+1 << " :\t\t";
				ConsoleControl::showInsertedLine(modifiedFileData[modifiedFileIndex]);

				++modifiedFileIndex;
				++currentIndex;
				continue;
			}
		}

		//*********************************************   deletions on modified file  ********************************************
		if (originalFileIndex < maxOriginalFileIndex) {
			if (originalFileLinesStatus[originalFileIndex].getLinesStatus() == LINE_DELETED) {
				outputFileStream << "Deleted on " << originalFileIndex+1 << " : " << originalFileData[originalFileIndex] << endl;

				cout << currentIndex+1 << "\t: ";
				cout << "Deleted on " << originalFileIndex+1 << " :\t";
				ConsoleControl::showDeletedLine(originalFileData[originalFileIndex]);

				++originalFileIndex;
				++currentIndex;
				continue;
			}
		}


		if (modifiedFileIndex < maxModifiedFileIndex)
			correspondentModifiedIndexInOriginalFile = modifiedFileMovedLinesIndexsInOriginalFile[modifiedFileIndex];

		//não deve acontecer mas...
		if (correspondentModifiedIndexInOriginalFile == -1) {
			++modifiedFileIndex;
			++currentIndex;
			continue;
		}

		//check
		if (modifiedFileIndex < maxModifiedFileIndex) {
			switch (originalFileLinesStatus[correspondentModifiedIndexInOriginalFile].getLinesStatus()) {
				case LINE_EQUAL: {
					cout << currentIndex+1 << "\t: ";
					cout << "Equal:\t\t";
					ConsoleControl::showEqualLine(originalFileData[correspondentModifiedIndexInOriginalFile]);

					break;
				}

				case LINE_MODIFIED: {
					outputFileStream << "Modified on " << correspondentModifiedIndexInOriginalFile+1 << " : " << modifiedFileData[modifiedFileIndex] << endl;

					cout << currentIndex+1 << "\t: ";
					cout << "Modified-Orig:\t";
					for (size_t originalCharsIndex = 0; originalCharsIndex < originalFileData[correspondentModifiedIndexInOriginalFile].size(); ++originalCharsIndex) {
						if (originalFileLinesStatus[correspondentModifiedIndexInOriginalFile].getLineCharsChangedOnOriginalFile()[originalCharsIndex])
							ConsoleControl::showChangedChar(originalFileData[correspondentModifiedIndexInOriginalFile][originalCharsIndex]);
						else
							ConsoleControl::showUnChangedChar(originalFileData[correspondentModifiedIndexInOriginalFile][originalCharsIndex]);
					}

					cout << "\n\t  Modified-Modif:\t";
					for (size_t modifiedCharsIndex = 0; modifiedCharsIndex < modifiedFileData[modifiedFileIndex].size(); ++modifiedCharsIndex) {
						if (originalFileLinesStatus[correspondentModifiedIndexInOriginalFile].getLineCharsChangedOnModifiedFile()[modifiedCharsIndex])
							ConsoleControl::showChangedChar(modifiedFileData[modifiedFileIndex][modifiedCharsIndex]);
						else
							ConsoleControl::showUnChangedChar(modifiedFileData[modifiedFileIndex][modifiedCharsIndex]);
					}
					cout << "\n";

					break;
				}

				case LINE_MOVED: {
					outputFileStream << "Moved from " << correspondentModifiedIndexInOriginalFile+1 << " to " << modifiedFileIndex+1 << " : " << originalFileData[correspondentModifiedIndexInOriginalFile] << endl;

					cout << currentIndex+1 << "\t: ";
					cout << "Moved from " << correspondentModifiedIndexInOriginalFile+1 << " to " << modifiedFileIndex+1 << ":\t";
					ConsoleControl::showMovedLine(originalFileData[correspondentModifiedIndexInOriginalFile]);

					break;
				}

				case LINE_MOVED_AND_MODIFIED: {
					outputFileStream << "Moved from " << correspondentModifiedIndexInOriginalFile+1 << " to " << modifiedFileIndex+1 << " : " << modifiedFileData[modifiedFileIndex] << endl;

					cout << currentIndex+1 << "\t: ";
					cout << "Moved&Modif from " << correspondentModifiedIndexInOriginalFile+1 << ":\t";
					for (size_t originalCharsIndex = 0; originalCharsIndex < originalFileData[correspondentModifiedIndexInOriginalFile].size(); ++originalCharsIndex) {
						if (originalFileLinesStatus[correspondentModifiedIndexInOriginalFile].getLineCharsChangedOnOriginalFile()[originalCharsIndex])
							ConsoleControl::showChangedAndMovedChar(originalFileData[correspondentModifiedIndexInOriginalFile][originalCharsIndex]);
						else
							ConsoleControl::showUnChangedAndMovedChar(originalFileData[correspondentModifiedIndexInOriginalFile][originalCharsIndex]);
					}

					cout << "\n\t  Moved&Modif to " << modifiedFileIndex+1 << ":\t";
					for (size_t modifiedCharsIndex = 0; modifiedCharsIndex < modifiedFileData[modifiedFileIndex].size(); ++modifiedCharsIndex) {
						if (originalFileLinesStatus[correspondentModifiedIndexInOriginalFile].getLineCharsChangedOnModifiedFile()[modifiedCharsIndex])
							ConsoleControl::showChangedAndMovedChar(modifiedFileData[modifiedFileIndex][modifiedCharsIndex]);
						else
							ConsoleControl::showUnChangedAndMovedChar(modifiedFileData[modifiedFileIndex][modifiedCharsIndex]);
					}
					cout << "\n";

					break;
				}

				default: {
					break;
				}
			}
		}

		++currentIndex;
		++originalFileIndex;
		++modifiedFileIndex;
	}


	cout << "\n\n";
	utils::getUserInput();
}


/// Método que carrega o patch
void Diff::loadPatchFileCLI() {
	utils::clearConsoleScreen();

	string patchFilename = utils::getFileNameCin("\n  -> Introduza o nome do ficheiro de onde quer carregar o patchFile: ", "O nome do ficheiro que introduziu nao existe!\n", true);
	patchFileName = patchFilename;
	loadPatchFile(patchFileName);

	//parsePatchFile();
}


/// Método que mostra o ficheiro original depois de ser aplicado o patch (ou seja, tornou-se igual ai ficheiro modificado)
void Diff::showOriginalFilePatchedCLI() {
	utils::clearConsoleScreen();

	if (patchFileData.empty()) {
		loadPatchFileCLI();
	}

	for (size_t originalFilePatchedIndex = 0; originalFilePatchedIndex < originalFilePatched.size(); ++originalFilePatchedIndex) {
		if (originalFilePatchedLinesStatus[originalFilePatchedIndex] == LINE_INSERTED) {
			ConsoleControl::showInsertedLine(originalFilePatched[originalFilePatchedIndex]);
		} else if (originalFilePatchedLinesStatus[originalFilePatchedIndex] == LINE_DELETED) {
			ConsoleControl::showDeletedLine(originalFilePatched[originalFilePatchedIndex]);
		} else if (originalFilePatchedLinesStatus[originalFilePatchedIndex] == LINE_MODIFIED) {
			ConsoleControl::showChangedLine(originalFilePatched[originalFilePatchedIndex]);
		} else if (originalFilePatchedLinesStatus[originalFilePatchedIndex] == LINE_MOVED) {
			ConsoleControl::showMovedLine(originalFilePatched[originalFilePatchedIndex]);
		} else {
			ConsoleControl::showEqualLine(originalFilePatched[originalFilePatchedIndex]);
		}
	}


	cout << "\n\n";
	utils::getUserInput();
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </Diff console interface>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
vector<string>& Diff::getModifiedFileData() {
	return modifiedFileData;
}

vector<bool>& Diff::getModifiedFileLinesPresentedOnOriginal() {
	return modifiedFileLinesPresentedOnOriginal;
}

vector<int>& Diff::getModifiedFileMovedLinesIndexsInOriginalFile() {
	return modifiedFileMovedLinesIndexsInOriginalFile;
}

string Diff::getModifiedFileName() const {
	return modifiedFileName;
}

vector<string>& Diff::getOriginalFileData() {
	return originalFileData;
}

vector<LineInfo>& Diff::getOriginalFileLinesStatus() {
	return originalFileLinesStatus;
}

vector<int>& Diff::getOriginalFileMovedLinesIndexsInModifiedFile() {
	return originalFileMovedLinesIndexsInModifiedFile;
}

string Diff::getOriginalFileName() const {
	return originalFileName;
}

vector<string>& Diff::getOriginalFilePatched() {
	return originalFilePatched;
}

vector<LineChangeType>& Diff::getOriginalFilePatchedLinesStatus() {
	return originalFilePatchedLinesStatus;
}

vector<string>& Diff::getPatchFileData() {
	return patchFileData;
}

string Diff::getPatchFileName() const {
	return patchFileName;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void Diff::setModifiedFileData(const vector<string>& modifiedFileData) {
	this->modifiedFileData = modifiedFileData;
}

void Diff::setModifiedFileLinesPresentedOnOriginal(const vector<bool>& modifiedFileLinesPresentedOnOriginal) {
	this->modifiedFileLinesPresentedOnOriginal = modifiedFileLinesPresentedOnOriginal;
}

void Diff::setModifiedFileMovedLinesIndexsInOriginalFile(const vector<int>& modifiedFileMovedLinesIndexsInOriginalFile) {
	this->modifiedFileMovedLinesIndexsInOriginalFile = modifiedFileMovedLinesIndexsInOriginalFile;
}

void Diff::setModifiedFileName(string modifiedFileName) {
	this->modifiedFileName = modifiedFileName;
}

void Diff::setOriginalFileData(const vector<string>& originalFileData) {
	this->originalFileData = originalFileData;
}

void Diff::setOriginalFileLinesStatus(const vector<LineInfo>& originalFileLinesStatus) {
	this->originalFileLinesStatus = originalFileLinesStatus;
}

void Diff::setOriginalFileMovedLinesIndexsInModifiedFile(const vector<int>& originalFileMovedLinesIndexsInModifiedFile) {
	this->originalFileMovedLinesIndexsInModifiedFile = originalFileMovedLinesIndexsInModifiedFile;
}

void Diff::setOriginalFileName(string originalFileName) {
	this->originalFileName = originalFileName;
}

void Diff::setOriginalFilePatched(const vector<string>& originalFilePatched) {
	this->originalFilePatched = originalFilePatched;
}

void Diff::setOriginalFilePatchedLinesStatus(const vector<LineChangeType>& originalFilePatchedLinesStatus) {
	this->originalFilePatchedLinesStatus = originalFilePatchedLinesStatus;
}

void Diff::setPatchFileData(const vector<string>& patchFileData) {
	this->patchFileData = patchFileData;
}

void Diff::setPatchFileName(string patchFileName) {
	this->patchFileName = patchFileName;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
