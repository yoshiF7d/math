class Depth : public Symbol{
  public:
	Depth() : 
	Symbol("Depth","",id_Depth,0,Protected,0,nullptr,Expr_createString("{深さ}"))
	{}
	Expr* function(Expr* expr) override{
		int depth = mod((expr->next->next));
		(expr->next->next)->deleteRoot();
		return Integer :: create(depth);
	}
	int mod(Expr *expr){
		Expr *e;
		int depth=1,max=0,m;
		for(e=expr->child;e;e=e->next){
			m = mod(e);
			if(max < m){
				max = m;
			}
		}
		depth += max;
		return depth;
	}
		virtual void printdoc() override{
		cout << "                          Depth[expr] gives the maximum number of indices needed to specify any part of expr, plus 1.\n"
	}
}
