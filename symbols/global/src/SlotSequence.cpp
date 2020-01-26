#include <SymbolList.h>
#include <SymbolTable.h>
SlotSequence::SlotSequence() : Symbol("SlotSequence","##",global_SlotSequence,740,NHoldAll|Protected,pre,"",""){}
void SlotSequence::printdoc(){printf(
	"                          ## represents the sequence of arguments supplied to a pure function. \n"
	"                          ## represents the sequence of arguments supplied to a pure function, starting with the n\[Null]\[Null]^th argument. \n"
);}
