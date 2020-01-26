#include <SymbolList.h>
#include <SymbolTable.h>
Slot::Slot() : Symbol("Slot","#",global_Slot,740,NHoldAll|Protected,pre,"",""){}
void Slot::printdoc(){printf(
	"                          # represents the first argument supplied to a pure function.\n"
	"                          # n represents the nth argument.\n"
);}
