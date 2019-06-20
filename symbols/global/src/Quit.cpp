#include <SymbolList.h>
#include <SymbolTable.h>
Quit::Quit() : Symbol("Quit","",global_Quit,670,Locked|Protected,0,"",""){}
Expr* Quit::evaluate(Expr* expr){
	expr->deleteRoot();
	return nullptr;
}
void Quit::printdoc(){printf(
	"                          Quit this program.\n"
);}
