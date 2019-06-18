#include <SymbolList.h>
#include <SymbolTable.h>
Not::Not() : Symbol("Not","!",global_Not,230,Protected,0,"",""){}
void Not::printdoc(){printf(
	"                          !expr is the logical not function. It gives False if expr is True, and True if it is False.\n"
);}
