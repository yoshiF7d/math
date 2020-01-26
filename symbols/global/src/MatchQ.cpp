#include <SymbolList.h>
#include <SymbolTable.h>
MatchQ::MatchQ() : Symbol("MatchQ","",global_MatchQ,150,Protected,0,"",""){}
Expr* MatchQ::evaluate(Expr* expr){
	if(!(expr->child)){return expr;}
	if(!(expr->child->next)){
		std::cout << "MatchQ::argr: MatchQ called with 1 argument; 2 arguments are expected.\n";
		return expr;
	}
	Expr *e;
	if(mod((expr->child),(expr->child->next))){
		e = expr->replace(new Expr(global_True));
	}else{
		e = expr->replace(new Expr(global_False));
	}
	delete expr;
	return e;
}
bool MatchQ::mod(Expr* expr, Expr* form){
	return true;	
}
bool MatchQ::sm(Expr* e1, Expr* e2){
	if(e1->childCount() == e2->childCount()){
		Expr* c1 = e1->child;
		Expr* c2 = e2->child;
		for(;c1&&c2;c1=c1->next,c2=c2->next){
			if(!sm(c1,c2)){
				return false;
			}
		}
		return true;
	}
	return false;
}
bool MatchQ::cm(Expr* e1, Expr* e2){
	if(e1->symbol != e2->symbol){return false;}
	if(e1->child){
		Expr* c1 = e1->child;
		Expr* c2 = e2->child;
		for(;c1&&c2;c1=c1->next,c2=c2->next){
			if(!cm(c1,c2)){
				return false;
			}
		}
	}
	return true;
}
