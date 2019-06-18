#include <SymbolList.h>
#include <SymbolTable.h>
AtomQ::AtomQ() : Symbol("AtomQ","",global_AtomQ,670,Protected,0,"",""){}
Expr *AtomQ::function(Expr *expr){
	if(!(expr->child)){return expr;}
	if(mod((expr->child))){
		expr->symbol = SymbolTable::get(global_True);
	}else{
		expr->symbol = SymbolTable::get(global_False);
	}
	(expr->child)->deleteRoot();
	(expr->child)=NULL;
	return expr;
}
bool AtomQ::mod(Expr *expr){
	switch(expr->symbol->id){
	  case global_Integer:
	  case global_Real:
	  case global_String:
		return true;
	  default:
		return false;
	}
}
void AtomQ::printdoc(){printf(
	"                          AtomQ[expr] yields True if expr is an expression which cannot be divided into subexpressions, and yields False otherwise.\n"
);}
