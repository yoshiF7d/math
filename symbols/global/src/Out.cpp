#include <SymbolList.h>
#include <SymbolTable.h>
Out::Out() : Symbol("Out","%",global_Out,670,Listable|HoldFirst|Protected,pre,"",""){}
void Out::printdoc(){printf(
	"                          %% n or Out[n] is a global object that is assigned to be the value produced on the n th output line.\n"
);}
