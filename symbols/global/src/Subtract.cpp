#include <SymbolList.h>
#include <SymbolTable.h>
Subtract::Subtract() : Symbol("Subtract","-",global_Subtract,310,Listable|NumericFunction|Protected,left,"",""){}
void Subtract::printdoc(){printf(
	"                          x - y is equivalent to x + (-1 * y).\n"
);}
