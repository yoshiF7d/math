#include <SymbolList.h>
#include <SymbolTable.h>
SameQ::SameQ() : Symbol("SameQ","===",global_SameQ,290,Protected,none,"",""){}
void SameQ::printdoc(){printf(
	"                          lhs === rhs yields True if the expression lhs is identical to rhs, and yields False otherwise.\n"
);}
