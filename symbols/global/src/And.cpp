#include <SymbolList.h>
#include <SymbolTable.h>
And::And() : Symbol("And","&&",global_And,215,Flat|HoldAll|OneIdentity|Protected,left,"",""){}
void And::printdoc(){printf(
	"                          e1 && e2 && ... is the logical AND function.\n"
	"                          It evaluates its arguments in order, giving False immediately \n"
	"                          if any of them are False, and True if they are all True.\n"
);}
