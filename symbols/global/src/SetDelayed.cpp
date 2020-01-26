#include <SymbolList.h>
#include <SymbolTable.h>
SetDelayed::SetDelayed() : Symbol("SetDelayed",":=",global_SetDelayed,40,HoldAll|Protected|SequenceHold,right,"",""){}
void SetDelayed::printdoc(){printf(
	"                          lhs := rhs assigns rhs to be the delayed value of lhs.\n"
	"                          rhs is maintained in an unevaluated form. \n"
	"                          When lhs appears, it is replaced by rhs, evaluated afresh each time.\n"
);}
