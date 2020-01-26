#include <SymbolList.h>
#include <SymbolTable.h>
RuleDelayed::RuleDelayed() : Symbol("RuleDelayed",":>",global_RuleDelayed,120,HoldRest|Protected|SequenceHold,right,"",""){}
void RuleDelayed::printdoc(){printf(
	"                          lhs:>rhs represents a rule that transforms lhs to rhs, evaluating rhs only after the rule is used.\n"
);}
