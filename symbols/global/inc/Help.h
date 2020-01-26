#include <Expr.h>
#include <Symbol.h>
class Help : public Symbol{
public :
	Help();
	Expr *evaluate(Expr *expr) override;	void printdoc() override;

};
