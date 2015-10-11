#ifndef DIFF_H_
#define DIFF_H_


/**\file Diff.h
 * \brief Classe que trata da gest�o da compara��o de dois ficheiros.
 *
 * @version CAL1011_2MIEIC6_8_TG2_1 - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <limits.h>


#include "Exceptions.h"
#include "defs.h"
#include "utils.h"
#include "LineInfo.h"
#include "EditDistance.h"
#include "LCS.h"
#include "../ConsoleControl/ConsoleControl.h"

using std::cout;
using std::cerr;
using std::flush;
using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;
using std::vector;
using std::min;
using std::max;



//################################################################   Diff   ######################################################################
/**
 * Classe que trata da gest�o da compara��o de dois ficheiros.
 */
class Diff {
private:
//=============================================================   <private>   ====================================================================
    string originalFileName;
    string modifiedFileName;
    string patchFileName;
    vector<string> originalFileData;
    vector<string> modifiedFileData;

    vector<string> patchFileData;
    vector<string> originalFilePatched;
    vector<LineChangeType> originalFilePatchedLinesStatus;

    vector<LineInfo> originalFileLinesStatus;
    vector<int> originalFileMovedLinesIndexsInModifiedFile;
    vector<int> modifiedFileMovedLinesIndexsInOriginalFile;
    vector<bool> modifiedFileLinesPresentedOnOriginal;
//=============================================================   </private>   ===================================================================
public:
//==============================================================   <public>   ====================================================================
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    /// Default constructor de Diff, que inicializa as estruturas auxiliares
    Diff(string originalFileName, string modifiedFileName, string patchFilename);

    /// Default destructor de Diff
    virtual ~Diff();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Diff loads-saves>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    /**
     * M�todo que carrega um ficheiro para um vector de strings
     * Lan�a excep��o FileDoesntExistException se n�o conseguir abrir o ficheiro
     * @param filename nome do ficheiro a carregar
     * @param fileData vector onde ir� guardar os dados
     */
    void loadFile(string filename, vector <string>& fileData) throw(FileDoesntExistException);

    /**
     * M�todo que carrega o ficheiro de patch
     * @param filename nome do ficheiro
     */
    void loadPatchFile(string filename) throw(FileDoesntExistException);
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </Diff loads-saves>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Diff analysis algoritms>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    /// M�todo que analiza os 2 ficheiros actualziando as estruturas auxiliares necess�rias para fazer o output da diferen�a entre eles
    void analyzeFiles();

    /// M�todo que encontra as corrspond�ncias entre linhas que possam ter mudado de posi��o entre os 2 ficheiros
    void findCorrespondentLines();

    /// M�todo que faz o parse da patchFile de forma a reconstituir o ficheiro modificado a partir do original e de um outro com as diferen�as entre os 2
    void parsePatchFile();

    /// M�todo auxiliar de parsePatchFile que calcula o vector com os indices de destino das modifica��es na sua forma inversa
    vector <int> calculateReverseIndexes();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </Diff analysis algoritms>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <Diff console interface>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    /**
     * M�todo que mostra um ficheiro na interface CLI
     * @param fileData vector de strings com os dados do ficheiro
     */
    void showFileCLI(const vector <string>& fileData);

	/// M�todo que mostra o ficheiro original na interface CLI
	void showOriginalFileCLI();

	/// M�todo que mostra o ficheiro modificado na interface CLI
	void showModifiedFileCLI();

	/// M�todo que mostra o ficheiro de patch na interface CLI
	void showPatchFileCLI();

	/// M�todo que mostra na interface CLI as diferen�as entre os 2 ficheiros
	void showModifiedFileChangesAndCreatePatchCLI();


	/// M�todo que carrega o patch
	void loadPatchFileCLI();

	/// M�todo que mostra o ficheiro original depois de ser aplicado o patch (ou seja, tornou-se igual ai ficheiro modificado)
	void showOriginalFilePatchedCLI();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </Diff console interface>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    vector<string>& getModifiedFileData();
    vector<bool>& getModifiedFileLinesPresentedOnOriginal();
    vector<int>& getModifiedFileMovedLinesIndexsInOriginalFile();
    string getModifiedFileName() const;
    vector<string>& getOriginalFileData();
    vector<LineInfo>& getOriginalFileLinesStatus();
    vector<int>& getOriginalFileMovedLinesIndexsInModifiedFile();
    string getOriginalFileName() const;
    vector<string>& getOriginalFilePatched();
    vector<LineChangeType>& getOriginalFilePatchedLinesStatus();
    vector<string>& getPatchFileData();
    string getPatchFileName() const;
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    void setModifiedFileData(const vector<string>& modifiedFileData);
    void setModifiedFileLinesPresentedOnOriginal(const vector<bool>& modifiedFileLinesPresentedOnOriginal);
    void setModifiedFileMovedLinesIndexsInOriginalFile(const vector<int>& modifiedFileMovedLinesIndexsInOriginalFile);
    void setModifiedFileName(string modifiedFileName);
    void setOriginalFileData(const vector<string>& originalFileData);
    void setOriginalFileLinesStatus(const vector<LineInfo>& originalFileLinesStatus);
    void setOriginalFileMovedLinesIndexsInModifiedFile(const vector<int>& originalFileMovedLinesIndexsInModifiedFile);
    void setOriginalFileName(string originalFileName);
    void setOriginalFilePatched(const vector<string>& originalFilePatched);
    void setOriginalFilePatchedLinesStatus(const vector<LineChangeType>& originalFilePatchedLinesStatus);
    void setPatchFileData(const vector<string>& patchFileData);
    void setPatchFileName(string patchFileName);
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//==============================================================   </public>   ===================================================================
};


#endif /* DIFF_H_ */
