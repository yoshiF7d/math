#include <SymbolList.h>
#include <SymbolTable.h>
Unequal::Unequal() : Symbol("Unequal","!=",global_Unequal,290,Protected,none,"",""){}
void Unequal::printdoc(){printf(
	"                          lhs != rhs returns False if lhs and rhs are identical.\n"
);}
