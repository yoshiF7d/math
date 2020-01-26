#include <SymbolList.h>
#include <SymbolTable.h>
PostApply::PostApply() : Symbol("PostApply","//",internal_PostApply,640,Protected|HoldAll,left,"",""){}
Expr* PostApply::preEvaluate(Expr* expr){
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
void PostApply::printdoc(){printf(
	"                          PostApply[expr,f] or expr//f evaluates to f[expr].\n"
);}
