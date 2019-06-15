#include <SymbolList.h>
#include <SymbolTable.h>
Depth::Depth() : Symbol("Depth","",global_Depth,0,Protected,0,"","{深さ}"){}
Expr* Depth::function(Expr* expr){
	int depth = mod((expr->child));
	(expr->child)->deleteRoot();
	return Integer::create(depth);
}
int Depth::mod(Expr *expr){
	Expr *e;
	int depth=1,max=0,m;
	for(e=(expr->child);e;e=e->next){
		m = mod(e);
		if(max < m){
			max = m;
		}
	}
	depth += max;
	return depth;
}
