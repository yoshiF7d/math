#include <Expr.h>
#include <Symbol.h>
class AtomQ : public Symbol{
public :
	AtomQ();
	Expr *function(Expr *expr) override;
	static bool mod(Expr *expr);	void printdoc() override;

};
