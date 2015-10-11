#ifndef LCS_H_
#define LCS_H_


/**\file LCS.h
 * \brief Classe que calcula a maior subsequência comum entre duas strings.
 *
 * @version CAL1011_2MIEIC6_8_TG2_1 - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::max;
using std::reverse;



//################################################################   LCS   #######################################################################
/**
 * Classe que calcula a maior subsequência comum entre duas strings.
 */
class LCS {
private:
//=============================================================   <private>   ====================================================================
	string text;
	string pattern;

	string textOptimized;
	string patternOptimized;

	size_t textAndPatternInitialIndex;
	size_t textFinalIndex;
	size_t patternFinalIndex;

	string LCSFound;

	vector < vector <int> > subSequenceLengths;
	bool subSequenceLengthsValid;
//=============================================================   </private>   ===================================================================

public:
//==============================================================   <public>   ====================================================================

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/// Default constructor de LCS
	LCS();

	/**
	 * Contructor de LCS
	 * @param _text texto que será analisado
	 * @param _pattern padrão que será usado nessa análise
	 */
	LCS(string _text, string _pattern);

	/// Default destructor de LCS
	virtual ~LCS();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <algoritmos de LCS>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/// Método que optimiza o algoritmo calcLCS(), tirando as partes comuns no inicio e fim de cada uma das strings
	void optimizeStringsToAnalize();

	/**
	 * Método que calcula a maior subcadeia comum das duas subtrings passadas no constructor
	 * @return Matrix com as distâncias ce edição
	 */
	vector < vector<int> >& calcLCS();

	/**
	 * Determinação da LCS usando a matriz calculada em calcLCS()
	 * @return LCS das duas strings
	 */
	string findLCS();

	/// Método que permite mostrar a matriz determinada por calcLCS() para poder confirmar o correcto funcuionamento do programa
	void showSubSequenceLengths();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </algoritmos de LCS>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    string getLCSFound() const;
    string getPattern() const;
    size_t getPatternFinalIndex() const;
    string getPatternOptimized() const;
    vector<vector<int> > getSubSequenceLengths() const;
    bool getSubSequenceLengthsValid() const;
    string getText() const;
    size_t getTextAndPatternInitialIndex() const;
    size_t getTextFinalIndex() const;
    string getTextOptimized() const;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    void setLCSFound(string LCSFound);
    void setPattern(string pattern);
    void setPatternFinalIndex(size_t patternFinalIndex);
    void setPatternOptimized(string patternOptimized);
    void setSubSequenceLengths(vector<vector<int> > subSequenceLengths);
    void setSubSequenceLengthsValid(bool subSequenceLengthsValid);
    void setText(string text);
    void setTextAndPatternInitialIndex(size_t textAndPatternInitialIndex);
    void setTextFinalIndex(size_t textFinalIndex);
    void setTextOptimized(string textOptimized);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
};

#endif /* LCS_H_ */
