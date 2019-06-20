#include <SymbolList.h>
#include <SymbolTable.h>
Depth::Depth() : Symbol("Depth","",global_Depth,0,Protected,0,"","{深さ}"){}
Expr* Depth::evaluate(Expr* expr){
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
void Depth::printdoc(){printf(
	"                          Depth[expr] gives the maximum number of indices needed to specify any part of expr, plus 1.\n"
);}
