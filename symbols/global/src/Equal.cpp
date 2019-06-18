#include <SymbolList.h>
#include <SymbolTable.h>
Equal::Equal() : Symbol("Equal","==",global_Equal,290,Protected,none,"",""){}
void Equal::printdoc(){printf(
	"                          lhs == rhs returns True if lhs and rhs are identical.\n"
);}
