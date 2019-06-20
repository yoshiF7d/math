#include <Expr.h>
#include <Symbol.h>
class FullForm : public Symbol{
public :
	FullForm();
	static Expr* mod(Expr* expr);
	Expr* evaluate(Expr* expr) override;	void printdoc() override;

};
