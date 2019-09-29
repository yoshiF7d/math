#include <SymbolList.h>
#include <SymbolTable.h>
PreApply::PreApply() : Symbol("PreApply","@",internal_PreApply,640,Protected|HoldAll,pre,"",""){}
Expr* PreApply::preEvaluate(Expr* expr){
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
void PreApply::printdoc(){printf(
	"                          PreApply[expr,f] or f@expr evaluates to f[expr].\n"
);}
