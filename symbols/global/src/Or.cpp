#include <SymbolList.h>
#include <SymbolTable.h>
Or::Or() : Symbol("Or","||",global_Or,215,Flat|HoldAll|OneIdentity|Protected,left,"",""){}
void Or::printdoc(){printf(
	"                          e1 || e2 || ... is the logical OR function.\n"
	"                          It evaluates its arguments in order, giving True immediately \n"
	"                          if any of them are True, and False if they are all False.\n"
);}
