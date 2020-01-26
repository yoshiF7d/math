#include <Expr.h>
#include <Symbol.h>
class ShowOperators : public Symbol{
public :
	ShowOperators();
	Expr* evaluate(Expr *expr) override;	void printdoc() override;

};
