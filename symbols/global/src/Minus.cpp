#include <SymbolList.h>
#include <SymbolTable.h>
Minus::Minus() : Symbol("Minus","-",global_Minus,480,Listable|NumericFunction|Protected,pre,"",""){}
void Minus::printdoc(){printf(
	"                          -x is arithmetic negation of x.\n"
);}
