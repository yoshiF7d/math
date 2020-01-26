#include <SymbolList.h>
#include <SymbolTable.h>
Pattern::Pattern() : Symbol("Pattern",":",global_Pattern,150,Protected,one,"",""){}
void Pattern::printdoc(){printf(
	"                          s:obj\n"
	"                          represents the pattern object obj, assigned the name s.\n"
);}
