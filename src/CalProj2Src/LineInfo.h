#ifndef LINEINFO_H_
#define LINEINFO_H_

/**\file LineInfo.h
 * \brief Classe que contêm a informação relacionada com uma linha de um ficheiro.
 *
 * @version CAL1011_2MIEIC6_8_TG2_1 - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */


#include <vector>
#include <string>

using std::vector;
using std::string;


/// Enumeração que identifica que tipo de alteração uma linha de um ficheiro sofreu
enum LineChangeType { LINE_EQUAL, LINE_INSERTED, LINE_DELETED, LINE_MODIFIED, LINE_MOVED, LINE_MOVED_AND_MODIFIED };


//##############################################################   LineInfo   ####################################################################
/**
 * Classe que contêm a informação relacionada com uma linha de um ficheiro.
 */
class LineInfo {
private:
//=============================================================   <private>   ====================================================================
	vector <bool> lineCharsChangedOnOriginalFile;
	vector <bool> lineCharsChangedOnModifiedFile;
	LineChangeType linesStatus;
//=============================================================   </private>   ===================================================================

public:
//==============================================================   <public>   ====================================================================
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/// Default constructor de LineInfo
	LineInfo();

	/// Default destructor de LineInfo
	virtual ~LineInfo();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    vector<bool>& getLineCharsChangedOnModifiedFile();
    vector<bool>& getLineCharsChangedOnOriginalFile();
    LineChangeType getLinesStatus() const;
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    void setLineCharsChangedOnModifiedFile(const vector<bool>& lineCharsChangedOnModifiedFile);
    void setLineCharsChangedOnOriginalFile(const vector<bool>& lineCharsChangedOnOriginalFile);
    void setLinesStatus(LineChangeType linesStatus);
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//==============================================================   </public>   ===================================================================
};


#endif /* LINEINFO_H_ */
