#include <SymbolList.h>
#include <SymbolTable.h>
Help::Help() : Symbol("Help","?",global_Help,1,Locked|Protected|HoldAll,post,"",""){}
Expr *Help::evaluate(Expr *expr){
	if((expr->child)){
		SymbolTable::print((expr->child)->symbol->id);
	}else{
		SymbolTable::print();
	}
	return expr;
}
void Help::printdoc(){printf(
	"                          Help shows informations about all symbols in eqsolv3.\n"
	"                          ?symbol or Help[symbol] shows information about a symbol.\n"
	"                          Help[\"Context`\"] shows informations in the specified context.\n"
);}
