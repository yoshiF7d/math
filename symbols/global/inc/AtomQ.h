#include <Expr.h>
#include <Symbol.h>
class AtomQ : public Symbol{
public :
	AtomQ();
	Expr *function(Expr *expr);
	static bool mod(Expr *expr);
};
