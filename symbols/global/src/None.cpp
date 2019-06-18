#include <SymbolList.h>
#include <SymbolTable.h>
None::None() : Symbol("None","",global_None,670,Locked|Protected,0,"",""){}
void None::printdoc(){printf(
	"                          None is a setting used for certain options.\n"
);}
