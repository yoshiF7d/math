#include <SymbolList.h>
#include <SymbolTable.h>
Divide::Divide() : Symbol("Divide","/",global_Divide,470,Listable|NumericFunction|Protected,left,"",""){}
void Divide::printdoc(){printf(
	"                          x/y or Divide[x,y] is equivalent to xy^-1.\n"
);}
