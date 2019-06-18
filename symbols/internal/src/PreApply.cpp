#include <SymbolList.h>
#include <SymbolTable.h>
PreApply::PreApply() : Symbol("PreApply","@",internal_PreApply,640,Protected|HoldAll,pre,"",""){}
void PreApply::printdoc(){printf(
	"                          PreApply[expr,f] or f@expr evaluates to f[expr].\n"
);}
