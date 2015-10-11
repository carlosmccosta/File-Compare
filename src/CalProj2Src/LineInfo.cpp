/**\file LineInfo.cpp
 * \brief Implementação da classe LineInfo
 *
 * @version CAL1011_2MIEIC6_8_TG2_1 - 10-11 - MIEIC
 * @author Carlos Miguel Correia da Costa - ei09097
 */

#include "LineInfo.h"


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/// Default constructor de LineInfo
LineInfo::LineInfo() : linesStatus(LINE_EQUAL) {}


/// Default destructor de LineInfo
LineInfo::~LineInfo() {}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <constructors-destructors>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<




//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
vector<bool>& LineInfo::getLineCharsChangedOnModifiedFile() {
	return lineCharsChangedOnModifiedFile;
}

vector<bool>& LineInfo::getLineCharsChangedOnOriginalFile() {
	return lineCharsChangedOnOriginalFile;
}

LineChangeType LineInfo::getLinesStatus() const {
	return linesStatus;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </gets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   <sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void LineInfo::setLineCharsChangedOnModifiedFile(const vector<bool>& lineCharsChangedOnModifiedFile) {
	this->lineCharsChangedOnModifiedFile = lineCharsChangedOnModifiedFile;
}

void LineInfo::setLineCharsChangedOnOriginalFile(const vector<bool>& lineCharsChangedOnOriginalFile) {
	this->lineCharsChangedOnOriginalFile = lineCharsChangedOnOriginalFile;
}

void LineInfo::setLinesStatus(LineChangeType linesStatus) {
	this->linesStatus = linesStatus;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   </sets>   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
