#include <Expr.h>
#include <Symbol.h>
class Depth : public Symbol{
public :
	Depth();
	Expr* evaluate(Expr* expr) override;
	int mod(Expr *expr);	void printdoc() override;

};
