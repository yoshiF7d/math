#include <Expr.h>
#include <Symbol.h>
class Quit : public Symbol{
public :
	Quit();
	Expr* evaluate(Expr* expr) override;	void printdoc() override;

};
