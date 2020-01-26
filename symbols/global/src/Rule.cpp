#include <SymbolList.h>
#include <SymbolTable.h>
Rule::Rule() : Symbol("Rule","->",global_Rule,120,Locked|Protected,right,"",""){}
void Rule::printdoc(){printf(
	"                          lhs->rhs represents a rule that transforms lhs to rhs.\n"
);}
