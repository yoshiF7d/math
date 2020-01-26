#include <SymbolList.h>
#include <SymbolTable.h>
Function::Function() : Symbol("Function","&",global_Function,90,HoldAll|Protected,post,"",""){}
void Function::printdoc(){printf(
	"                          Lambda[body] or body& is a pure function. The formal parameters are # (or #1), #2, etc.\n"
	"                          Lambda[x,body] is a pure function with a single formal parameter x.\n"
	"                          Lambda[{Subscript[x, 1],Subscript[x, 2],\[Ellipsis]},body] is a pure function with a list of formal parameters.\n"
);}
