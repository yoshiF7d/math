#include <Expr.h>
#include <Symbol.h>
class AtomQ : public Symbol{
public :
	AtomQ();
	Expr *evaluate(Expr *expr) override;
	static bool mod(Expr *expr);	void printdoc() override;

};
