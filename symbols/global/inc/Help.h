#include <Expr.h>
#include <Symbol.h>
class Help : public Symbol{
public :
	Help();
	Expr *function(Expr *expr) override;	void printdoc() override;

};
