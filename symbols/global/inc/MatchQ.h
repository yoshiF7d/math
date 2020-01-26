#include <Expr.h>
#include <Symbol.h>
class MatchQ : public Symbol{
public :
	MatchQ();
	Expr* evaluate(Expr* expr) override;
	static bool mod(Expr* expr, Expr* form);
	static bool sm(Expr* e1, Expr* e2);
	static bool cm(Expr* e1, Expr* e2);
};
