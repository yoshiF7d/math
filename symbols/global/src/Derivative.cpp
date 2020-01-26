#include <SymbolList.h>
#include <SymbolTable.h>
Derivative::Derivative() : Symbol("Derivative","'",global_Derivative,670,NHoldAll,post,"",""){}
void Derivative::printdoc(){printf(
	"                          f' represents the derivative of a function f of one argument. \n"
);}
