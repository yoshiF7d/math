#include <SymbolList.h>
#include <SymbolTable.h>
AtomQ::AtomQ() : Symbol("AtomQ","",global_AtomQ,670,Protected,0,"",""){}
Expr *AtomQ::evaluate(Expr *expr){
	if(!(expr->child)){return expr;}
	Expr *e;
	if(mod((expr->child))){
		e=expr->replace(new Expr(global_True));
	}else{
		e=expr->replace(new Expr(global_False));
	}
	delete expr;
	return e;
}
bool AtomQ::mod(Expr *expr){
	switch(expr->symbol->id){
	  case global_Integer:
	  case global_Real:
	  case global_String:
	  case internal_SymbolContainer:
		return true;
	  default:
		return false;
	}
}
void AtomQ::printdoc(){printf(
	"                          AtomQ[expr] yields True if expr is an expression which cannot be divided into subexpressions, and yields False otherwise.\n"
);}
