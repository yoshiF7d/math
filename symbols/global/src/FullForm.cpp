#include <SymbolList.h>
#include <SymbolTable.h>
FullForm::FullForm() : Symbol("FullForm","",global_FullForm,670,Protected,0,"",""){}
Expr* FullForm::mod(Expr* expr){
	std::string buf = expr->toString();
	if(!expr){std::cout << "null"; return expr;}
	std::cout << buf;
	if(expr->child){
		std::cout << "[";
		for(Expr *e=(expr->child);e;e=e->next){
			FullForm::mod(e);
			if(e->next){std::cout << ",";}
		}
		std::cout << "]";
	}
	return expr;
}
Expr* FullForm::evaluate(Expr* expr){
	if(!expr->child){return expr;}
	mod((expr->child));
	std::cout << std::endl;
	return expr;
}
void FullForm::printdoc(){printf(
	"                          FullForm[expr] prints as the full form of expr, with no special syntax.\n"
);}
