#include <SymbolList.h>
#include <SymbolTable.h>
Bracket::Bracket() : Symbol("Bracket","[]",internal_Bracket,1000,Protected,bracket,"",""){}
Expr* Bracket::preEvaluate(Expr* expr){
	if(!(expr->child)){return expr;}
	if((expr->child->next)){
		//if($00->symbol->associativity & BINARY){$00->deleteChildren();}
		if(!(expr->child)->child){
			Expr *e = (expr->child->next);
			(expr->child)->isolate();
			e = expr->replace((expr->child)->appendChild(e));
			delete expr;
			expr = e;
		}
	}
	return expr;
}
