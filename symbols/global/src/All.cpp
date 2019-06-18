#include <SymbolList.h>
#include <SymbolTable.h>
All::All() : Symbol("All","",global_All,670,Locked|Protected,0,"",""){}
void All::printdoc(){printf(
	"                          All is a setting used for certain options. In Part and related functions,\n"
	"                          All specifies all parts at a particular level.\n"
);}
