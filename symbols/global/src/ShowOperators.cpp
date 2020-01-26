#include <SymbolList.h>
#include <SymbolTable.h>
ShowOperators::ShowOperators() : Symbol("ShowOperators","",global_ShowOperators,670,Flat|OneIdentity|Protected,0,"",""){}
Expr* ShowOperators::evaluate(Expr *expr){
	if((expr->child)){
		SymbolTable::parser->print();
	}
	return expr;
}
void ShowOperators::printdoc(){printf(
	"                          ShowOperators[] shows built-in operators.\n"
);}
