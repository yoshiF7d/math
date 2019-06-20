#include <SymbolList.h>
#include <SymbolTable.h>
Parenthesis::Parenthesis() : Symbol("Parenthesis","()",internal_Parenthesis,1000,Protected,bracket,"",""){}
Expr* Parenthesis::preEvaluate(Expr* expr){
	if((expr->child)){
		Expr *e = expr->replace((expr->child));
		delete expr;
		expr = e;
	}
	return expr;
	}
