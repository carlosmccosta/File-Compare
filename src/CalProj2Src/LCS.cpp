/**\file LCS.cpp
 * \brief Ficheiro com a implementação da classe LCS.
 *
 * @version CAL1011_2MIEIC6_8_TG2_1 - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */


#include "LCS.h"


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/// Default constructor de LCS
LCS::LCS() : subSequenceLengthsValid(false) {}


/**
 * Contructor de LCS
 * @param _text texto que será analisado
 * @param _pattern padrão que será usado nessa análise
 */
LCS::LCS(string _text, string _pattern) : text(_text), pattern(_pattern), textOptimized(_text), patternOptimized(_pattern) {
	subSequenceLengths = vector < vector <int> >(_pattern.size() + 1, vector<int>(_text.size() + 1, 0));
	subSequenceLengthsValid = false;
}

/// Default destructor de LCS
LCS::~LCS() {}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <algoritmos de LCS>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/// Método que optimiza o algoritmo calcLCS(), tirando as partes comuns no inicio e fim de cada uma das strings
void LCS::optimizeStringsToAnalize() {
	textAndPatternInitialIndex = 0;
	textFinalIndex = text.size() - 1;
	patternFinalIndex = pattern.size() - 1;


	while ((textAndPatternInitialIndex < text.size()) &&
		   (textAndPatternInitialIndex < pattern.size()) &&
		   (text[textAndPatternInitialIndex] == pattern[textAndPatternInitialIndex])) {
		++textAndPatternInitialIndex;
	}


	while ((textFinalIndex < text.size()) &&
		   (patternFinalIndex < pattern.size()) &&
		   (text[textFinalIndex] == pattern[patternFinalIndex])) {

			--textFinalIndex;
			--patternFinalIndex;

			if (textAndPatternInitialIndex >= textFinalIndex) {
				textOptimized = "";
				patternOptimized = "";
				return;
			}
	}



	textOptimized = text.substr(textAndPatternInitialIndex, textFinalIndex);
	patternOptimized = pattern.substr(0, patternFinalIndex);

	subSequenceLengths.clear();
	subSequenceLengths = vector < vector <int> >(patternOptimized.size() + 1, vector<int>(textOptimized.size() + 1, 0));
}


/**
 * Método que calcula a maior subcadeia comum das duas subtrings passadas no constructor
 * @return Matrix com as os dados para obter a LCS
 */
vector<vector<int> >& LCS::calcLCS() {
	//optimizeStringsToAnalize();

	if (textOptimized.empty() || pattern.empty()) {
		subSequenceLengths.clear();
		LCSFound = "";
		return subSequenceLengths;
	}

	//1ª linha a 0
	for (size_t x = 0; x < subSequenceLengths[0].size(); ++x) {
		subSequenceLengths[0][x] = 0;
	}

	//1ª coluna a 0
	for (size_t y = 0; y < subSequenceLengths.size(); ++y) {
		subSequenceLengths[y][0] = 0;
	}



	for (size_t y = 0; y < patternOptimized.size(); ++y) {
		for (size_t x = 0; x < textOptimized.size(); ++x) {
			if (textOptimized[x] == patternOptimized[y])
				subSequenceLengths[y+1][x+1] = subSequenceLengths[y][x] + 1;
			else
				subSequenceLengths[y+1][x+1] = max(subSequenceLengths[y+1][x], subSequenceLengths[y][x+1]);
		}
	}

	subSequenceLengthsValid = true;

	return subSequenceLengths;
}


/**
 * Determinação da LCS usando a matriz calculada em calcLCS()
 * @return LCS das duas strings
 */
string LCS::findLCS() {
	if (text == pattern) {
		LCSFound = pattern;
		return LCSFound;
	}

	if (!subSequenceLengthsValid)
		calcLCS();

	if (subSequenceLengths.empty())
		return (string)"";

	string LCSstr;
	size_t x = subSequenceLengths[0].size() - 1;
	size_t y = subSequenceLengths.size() - 1;

	while (x > 0 && y > 0) {
		if (subSequenceLengths[y][x] != subSequenceLengths[y-1][x]) {
			LCSstr.append(1, patternOptimized[y-1]);
			--x;
		}

		--y;
	}

	reverse(LCSstr.begin(), LCSstr.end());
	LCSFound = LCSstr;
	return LCSstr;
}


/// Método que permite mostrar a matriz determinada por calcLCS() para poder confirmar o correcto funcuionamento do programa
void LCS::showSubSequenceLengths() {
	cout << "-------------------------------------------------------------------------------------------\n";
	cout << "|                        Matrix dos comprimentos das subsequencias                        |\n";
	cout << "-------------------------------------------------------------------------------------------\n";

	cout << "\nTexto:  \t\t" << text;
	cout << "\nTexto optimizado: \t" << textOptimized;

	cout << "\n\nPadrao: \t\t" << pattern;
	cout << "\nPadrao optimizado: \t" << patternOptimized << "\n\n";

	cout << "Matriz:\n" << endl;

	cout << "    ";
	for (size_t i = 0; i < textOptimized.size(); ++i) {
		cout << textOptimized[i] << " ";
	}

	cout << "\n";

	for (size_t i = 0; i < subSequenceLengths.size(); ++i) {
		if (i > 0)
			cout << patternOptimized[i-1] << " ";
		else
			cout << "  ";

		for (size_t j = 0; j < subSequenceLengths[i].size(); ++j) {
			cout << subSequenceLengths[i][j] << " ";
		}
		cout << "\n";
	}

	cout << "\n";

	cout << "Subsequencia encontrada: " << findLCS() << "\n" << endl;

}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </algoritmos de LCS>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
string LCS::getLCSFound() const {
	return LCSFound;
}

string LCS::getPattern() const {
	return pattern;
}

size_t LCS::getPatternFinalIndex() const {
	return patternFinalIndex;
}

string LCS::getPatternOptimized() const {
	return patternOptimized;
}

vector<vector<int> > LCS::getSubSequenceLengths() const {
	return subSequenceLengths;
}

bool LCS::getSubSequenceLengthsValid() const {
	return subSequenceLengthsValid;
}

string LCS::getText() const {
	return text;
}

size_t LCS::getTextAndPatternInitialIndex() const {
	return textAndPatternInitialIndex;
}

size_t LCS::getTextFinalIndex() const {
	return textFinalIndex;
}

string LCS::getTextOptimized() const {
	return textOptimized;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void LCS::setLCSFound(string LCSFound) {
	this->LCSFound = LCSFound;
}

void LCS::setPattern(string pattern) {
	this->pattern = pattern;
}

void LCS::setPatternFinalIndex(size_t patternFinalIndex) {
	this->patternFinalIndex = patternFinalIndex;
}

void LCS::setPatternOptimized(string patternOptimized) {
	this->patternOptimized = patternOptimized;
}

void LCS::setSubSequenceLengths(vector<vector<int> > subSequenceLengths) {
	this->subSequenceLengths = subSequenceLengths;
}

void LCS::setSubSequenceLengthsValid(bool subSequenceLengthsValid) {
	this->subSequenceLengthsValid = subSequenceLengthsValid;
}

void LCS::setText(string text) {
	this->text = text;
}

void LCS::setTextAndPatternInitialIndex(size_t textAndPatternInitialIndex) {
	this->textAndPatternInitialIndex = textAndPatternInitialIndex;
}

void LCS::setTextFinalIndex(size_t textFinalIndex) {
	this->textFinalIndex = textFinalIndex;
}

void LCS::setTextOptimized(string textOptimized) {
	this->textOptimized = textOptimized;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
