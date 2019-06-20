#include <Expr.h>
#include <Symbol.h>
class Evaluate : public Symbol{
public :
	Evaluate();
	Expr* evaluate(Expr *expr) override;	void printdoc() override;

};
