#include <SymbolList.h>
#include <SymbolTable.h>
Null::Null() : Symbol("Null","",global_Null,670,Locked|Protected,0,"",""){}
void Null::printdoc(){printf(
	"                          Null is a symbol used to indicate the absence of an expression or a result.\n"
	"                          It is not displayed in ordinary output. \n"
	"                          When Null appears as a complete output expression, no output is printed.\n"
);}
