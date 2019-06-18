#include <SymbolList.h>
#include <SymbolTable.h>
CompoundExpression::CompoundExpression() : Symbol("CompoundExpression",";",global_CompoundExpression,10,Protected,none,"",""){}
void CompoundExpression::printdoc(){printf(
	"                          expr_1;expr_2;... evaluates the expr_i in turn, giving the last one as the result.\n"
);}
