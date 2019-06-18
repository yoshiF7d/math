#include <Expr.h>
#include <Symbol.h>
class Evaluate : public Symbol{
public :
	Evaluate();
	Expr* function(Expr *expr) override;	void printdoc() override;

};
