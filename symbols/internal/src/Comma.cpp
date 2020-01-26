#include <SymbolList.h>
#include <SymbolTable.h>
Comma::Comma() : Symbol("Comma",",",internal_Comma,0,Protected,none,"",""){}
Expr* Comma::preEvaluate(Expr* expr){
	if((expr->child)){
		Expr *e = expr->replace((expr->child));
		delete expr;
		expr = e;
	}
	return expr;
}
