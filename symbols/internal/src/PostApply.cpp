#include <SymbolList.h>
#include <SymbolTable.h>
PostApply::PostApply() : Symbol("PostApply","//",internal_PostApply,640,Protected|HoldAll,left,"",""){}
void PostApply::printdoc(){printf(
	"                          PostApply[expr,f] or expr//f evaluates to f[expr].\n"
);}
