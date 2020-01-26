#include <SymbolList.h>
#include <SymbolTable.h>
ApplyLevelOne::ApplyLevelOne() : Symbol("ApplyLevelOne","@@@",global_ApplyLevelOne,620,Protected,right,"",""){}
Expr* ApplyLevelOne::preEvaluate(Expr* expr){
	if(!(expr->child)){return expr;}
	if((expr->child->next)){
		Expr *e = expr->replace(new Expr(global_Apply));
		e->appendChild(expr->child);
		delete expr;
		expr = e;
		e = new Expr(global_List);
		expr->appendChild(e->appendChild(Integer::create(1)));
	}
	return expr;
}
void ApplyLevelOne::printdoc(){printf(
	"                          f@@@expr is equivalent to Apply[f,expr,{1}]\n"
);}
