#include <SymbolList.h>
#include <SymbolTable.h>
Evaluate::Evaluate() : Symbol("Evaluate","",global_Evaluate,670,Locked|Protected,0,"","{評価}"){}
Expr* Evaluate::function(Expr *expr){
	Expr *e;
	if(!expr){return nullptr;}
  reeval:
	if(!expr->symbol){return expr;}
	/*
	if(!(expr->symbol->attributes & SequenceHold) && expr->symbol->id == global_Sequence){
		expr = Sequence(expr); goto reeval;
	}
	if(!(expr->symbol->attributes & HoldAllComplete)){
		for(e = $00;e;e=e->next){
			if(e->symbol->id == global_Sequence){e = Sequence(e);}
		}
	}
	*/
	/*
	if(expr->symbol->attributes & Listable){
		//Expr_printTree(expr);
		e=Thread::mod(expr,nunllptr,nullptr);
		if(e!=expr){
			expr=e;
			goto reeval;
		}
		expr=e;
	}
	if(expr->symbol->attributes & Flat){
		expr = Flatten::mod(expr,nullptr,0,-1);
		//Expr_printTree(expr);
	}
	*/
	//printAttributes(sd->attributes);
	//puts("e1");
	/*
	if(!((expr->symbol->attributes & HoldAllComplete) || (expr->symbol->attributes & HoldAll)) && $00){
		if(!(expr->symbol->attributes & HoldFirst)){
			expr->child = Evaluate::function(expr->child);
		}
		if(!(expr->symbol->attributes & HoldRest) && (e=expr->child->next)){
			for(;e;e=e->next){
				e = Evaluate::function(e);
			}
		}
	}
	//puts("e2");
	if(expr->symbol->attributes & Orderless){
		expr->child = Sort::mod(expr->child);
	}
	*/
	/*
	if(expr->symbol->builtinrules){
		e = Expr_copyRoot(expr->symbol->builtinrules);
		prev = expr;
		expr = Replace_mod(expr,e,0,0);
		Expr_deleteRoot(e);
		if(!SameQ_mod(prev,expr)){expr=Evaluate(expr);}
	}
	*/
	if(expr->symbol->id!=global_Evaluate){
		expr = expr->symbol->function(expr);
	}else{
		/*
		Expr_replace($0,e=$00);
		Expr_delete($0);
		$0 = e;
		*/
	}
	return expr;
}
void Evaluate::printdoc(){printf(
	"                          Evaluate[expr] evaluates expression expr.\n"
);}
