#include <SymbolList.h>
#include <SymbolTable.h>
PatternBlank::PatternBlank() : Symbol("PatternBlank","",internal_PatternBlank,730,Protected,0,"",""){}
Expr* PatternBlank::preEvaluate(Expr* expr){
	Expr *e = expr->replace(new Expr(global_Pattern));
	e->appendChild(expr->child);
	delete expr;
	expr = e;
	return expr;
}
void PatternBlank::printdoc(){printf(
	"                          The form s_ is equivalent to s:_\n"
);}
