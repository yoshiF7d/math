#include <SymbolList.h>
#include <SymbolTable.h>
False::False() : Symbol("False","",global_False,670,Locked|Protected,0,"",""){}
void False::printdoc(){printf(
	"                          False is the symbol for the Boolean value false.\n"
);}
