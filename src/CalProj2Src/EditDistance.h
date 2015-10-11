#ifndef EDITDISTANCE_H_
#define EDITDISTANCE_H_


/**\file EditDistance.h
 * \brief Classe que calcula a dist�ncia de edi��o entre 2 strings.
 *
 * @version CAL1011_2MIEIC6_8_TG2_1 - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */


#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::min;



//############################################################   EditDistance   ##################################################################
/**
 * Classe que calcula a dist�ncia de edi��o entre duas strings.
 */
class EditDistance {
private:
//=============================================================   <private>   ====================================================================
	string text;
	string pattern;
	int editDistance;
//=============================================================   </private>   ===================================================================

public:
//==============================================================   <public>   ====================================================================
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/// Default constructor de EditDistance
	EditDistance();

	/**
	 * Contrucotr de EditDistance
	 * @param _text texto a ser analisado
	 * @param _pattern padr�o a ser usado nessa an�lise
	 */
	EditDistance(string _text, string _pattern);

	/// Default destructor de EditDistance
	virtual ~EditDistance();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <algoritmos de editDistance>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/**
	 * M�todo que calcula a dist�ncia de edi��o entre 2 strings
	 * @param debug flag que indica se � para mostar a matriz com as subdist�ncias de edi��o calculadas
	 * @return dist�ncia de edi��o entre as 2 strings
	 */
	int calcEditDistance(bool debug = false);

	/**
	 * M�todo que mostra a matriz calculada em calcEditDistance(true)
	 * @param editDistances vector com a matriz das dist�ncias de edi��o interm�dias
	 */
	void showEditDistances(const vector < vector <int> >& editDistances);

	/**
	 * Vers�o optimizada para ter complexidade espacial de O(|T|)
	 * @return dist�ncia de edi��o entre as 2 strings
	 */
	int calcEditDistanceOptimized();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </algoritmos de editDistance>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    int getEditDistance() const;
    string getPattern() const;
    string getText() const;
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    void setEditDistance(int editDistance);
    void setPattern(string pattern);
    void setText(string text);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//==============================================================   </public>   ===================================================================
};

#endif /* EDITDISTANCE_H_ */
