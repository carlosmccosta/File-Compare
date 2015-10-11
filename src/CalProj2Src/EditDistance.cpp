/**\file EditDistance.cpp
 * \brief Ficheiro com a implementação da classe EditDistance.
 *
 * @version CAL1011_2MIEIC6_8_TG2_1 - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */

#include "EditDistance.h"


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/// Default constructor de EditDistance
EditDistance::EditDistance() : editDistance(-1) {}

/**
 * Contrucotr de EditDistance
 * @param _text texto a ser analisado
 * @param _pattern padrão a ser usado nessa análise
 */
EditDistance::EditDistance(string _text, string _pattern) : text(_text), pattern(_pattern), editDistance(-1) {}

/// Default destructor de EditDistance
EditDistance::~EditDistance() {}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <algoritmos de editDistance>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Método que calcula a distância de edição entre 2 strings
 * @param debug flag que indica se é para mostar a matriz com as subdistâncias de edição calculadas
 * @return distância de edição entre as 2 strings
 */
int EditDistance::calcEditDistance(bool debug) {
	if (text.empty())
		return pattern.size();

	if (pattern.empty())
		return text.size();

	if (text == pattern)
		return 0;


	size_t textSize = text.size();
	size_t patternSize = pattern.size();

	vector < vector <int> > editDistances(patternSize + 1, vector<int>(textSize + 1, 0));

	for (size_t i = 0; i <= patternSize; ++i) {
		editDistances[i][0] = (int)i;
	}

	for (size_t j = 0; j <= textSize; ++j) {
		editDistances[0][j] = (int)j;
	}

	for (size_t i = 1; i <= patternSize; ++i) {
		for (size_t j = 1; j <= textSize; ++j) {
			if (pattern[i-1] == text[j-1]) {
				editDistances[i][j] = editDistances[i-1][j-1];
			} else {
				editDistances[i][j] = min(editDistances[i-1][j-1] + 1, min(editDistances[i-1][j] + 1, editDistances[i][j-1] + 1));
			}
		}
	}

	editDistance = editDistances[patternSize][textSize];

	if (debug)
		showEditDistances(editDistances);

	return editDistances[patternSize][textSize];
}


/**
 * Método que mostra a matriz calculada em calcEditDistance(true)
 * @param editDistances vector com a matriz das distâncias de edição intermédias
 */
void EditDistance::showEditDistances(const vector < vector <int> >& editDistances) {
	cout << "-------------------------------------------------------------------------------------------\n";
	cout << "|                            Matrix dos tamanhos de edicao                                |\n";
	cout << "-------------------------------------------------------------------------------------------\n";

	cout << "\nTexto:  \t" << text;

	cout << "\n\nPadrao: \t" << pattern;

	cout << "\n\nMatriz:\n" << endl;

	cout << "    ";
	for (size_t i = 0; i < text.size(); ++i) {
		cout << text[i] << " ";
	}

	cout << "\n";

	for (size_t i = 0; i < editDistances.size(); ++i) {
		if (i > 0)
			cout << pattern[i-1] << " ";
		else
			cout << "  ";

		for (size_t j = 0; j < editDistances[i].size(); ++j) {
			cout << editDistances[i][j] << " ";
		}
		cout << "\n";
	}

	cout << "\n";

	cout << "Tamanho de edicao: " << editDistance << "\n" << endl;
}


/**
 * Versão optimizada para ter complexidade espacial de O(|T|)
 * @return distância de edição entre as 2 strings
 */
int EditDistance::calcEditDistanceOptimized() {
	if (text.empty())
		return pattern.size();

	if (pattern.empty())
		return text.size();

	if (text == pattern)
			return 0;

	size_t textSize = text.size();
	size_t patternSize = pattern.size();

	vector <int> editDistances(textSize + 1);
	int old, neww;

	for (size_t j = 0; j <= textSize; ++j)
		editDistances[j] = j;
	
	for (size_t i = 1; i <= patternSize; ++i) {
		old = editDistances[0];
		editDistances[0] = i;
		for (size_t j = 1; j <= textSize; ++j) {
			if (pattern[i-1] == text[j-1]) neww = old;
			else {
				neww = min(old, editDistances[j]);
				neww = min(neww, editDistances[j-1]);
				neww = neww + 1;
			}
			old = editDistances[j];
			editDistances[j] = neww;
		}
	}
	

	editDistance = editDistances[textSize];

	return editDistances[textSize];
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </algoritmos de editDistance>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
int EditDistance::getEditDistance() const {
	return editDistance;
}

string EditDistance::getPattern() const {
	return pattern;
}

string EditDistance::getText() const {
	return text;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void EditDistance::setEditDistance(int editDistance) {
	this->editDistance = editDistance;
}

void EditDistance::setPattern(string pattern) {
	this->pattern = pattern;
}

void EditDistance::setText(string text) {
	this->text = text;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
